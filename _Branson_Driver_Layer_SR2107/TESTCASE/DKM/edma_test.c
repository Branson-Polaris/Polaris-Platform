#include "test_def.h"
#include <cacheLib.h>
#include <semLib.h>
#include <subsys/dma/vxbDmaLib.h>

/*******************************************************************************
*
* tiEdma3SyncIsrCallBack - callback when DMA transfer done
*
* This routine is the callback function when DMA transfer is done.
*
* RETURNS: N/A
*
* ERRNO: N/A
*/

LOCAL void tiEdma3TestCallBack
    (
    void *  pArg
    )
    {
    SEM_ID  sem = (SEM_ID)pArg;

    if (SEM_ID_NULL != sem)
        {
        (void)semGive (sem);
        }
    }

/*******************************************************************************
*
* tiEdma3Test - test EDMA3 basic function
*
* This routine test EDMA3 basic function
*
* RETURNS: N/A
*
* ERRNO: N/A
*/

STATUS tiEdma3Test
    (
    UINT32  chanCnt
    )
    {
    int                     i;
    VXB_DMA_CHAN *          pChan[64];
    VXB_DMA_TX *            pTx[64];
    UINT32 *                pSrc    = NULL;
    UINT32 *                pDest   = NULL;
    UINT32                  size    = 1024;
    SEM_ID                  sem     = SEM_ID_NULL;
    VXB_DMA_SLAVE_CONFIG    config;
    STATUS                  ret = ERROR;
    UINT32                  cnt = 0;

    if (chanCnt > 64)
        {
        printf("failure: chanCnt > 64 !\n");
        return ERROR;
        }

    bzero ((char *)&pChan[0], (sizeof (VXB_DMA_CHAN *) * 64));
    bzero ((char *)&pTx[0], (sizeof (VXB_DMA_TX *) * 64));
    bzero ((char *)&config, sizeof (VXB_DMA_SLAVE_CONFIG));

    sem = semBCreate (SEM_Q_FIFO, SEM_EMPTY);
    if (SEM_ID_NULL == sem)
        {
        printf("failure: semBCreate failed!\n");
        goto test_exit;
        }

    pSrc = (UINT32 *)cacheDmaMalloc (size * chanCnt);
    if (NULL == pSrc)
        {
        printf("failure: allocate pSrc failed!\n");
        goto test_exit;
        }

    pDest = (UINT32 *)cacheDmaMalloc (size * chanCnt);
    if (NULL == pDest)
        {
        printf("failure: allocate pDest failed!\n");
        goto test_exit;
        }

    printf("pSrc = 0x%x, pDest = 0x%x\n", pSrc, pDest);

    for (i = 0; i < (size * chanCnt / sizeof (UINT32)); i++)
        {
        *(pSrc + i) = i;
        }

    bzero ((char *)pDest, size * chanCnt);

    printf("allocating channels...\n");
    for (i = 0; i < chanCnt; i++)
        {
        pChan[i] = vxbDmaChanAlloc (0);
        if (NULL == pChan[i])
            {
            break;
            }
        }
    cnt = i;
    printf("%d channels allocated\n", cnt);

    config.direction        = VXB_DMA_MEM_TO_MEM;
    config.destAddrWidth    = sizeof (UINT32);
    config.destMaxBurst     = size;
    config.dmaEvent         = -1;

    for (i = 0; i < cnt; i++)
        {
        if (OK != vxbDmaChanConfig (pChan[i], &config))
            {
            printf("failure: vxbDmaChanConfig failed!\n");
            goto test_exit;
            }
        }

    for (i = 0; i < cnt; i++)
        {
        pTx[i] = vxbDmaChanPreMemCpy (pChan[i],
            (VIRT_ADDR)(pSrc + size * i / sizeof (UINT32)),
            (VIRT_ADDR)(pDest + size * i / sizeof (UINT32)), size, 0);

        if (NULL == pTx[i])
            {
            printf("failure: vxbDmaChanPreMemCpy failed!\n");
            goto test_exit;
            }
        }

    for (i = 0; i < cnt; i++)
        {
        pTx[i]->fn = (VXB_DMA_COMPLETE_FN)tiEdma3TestCallBack;
        pTx[i]->pArg = (void *)sem;
        if (OK != vxbDmaChanStart (pTx[i]))
            {
            printf("failure: vxbDmaChanStart failed!\n");
            goto test_exit;
            }
        (void)semTake (sem, WAIT_FOREVER);
        }

    for (i = 0; i < (size * cnt / sizeof (UINT32)); i++)
        {
        if (*(pSrc + i) != *(pDest + i))
            {
            printf("failure: DmaTrans failed! "
                       "*(pSrc + i) = 0x%x, *(pDest + i) = 0x%x, i = %d\n",
                       *(pSrc + i), *(pDest + i), i);
            goto test_exit;
            }
        }
    
    ret = OK;

test_exit:
    if (NULL != pSrc)
        {
        (void)cacheDmaFree (pSrc);
        }

    if (NULL != pDest)
        {
        (void)cacheDmaFree (pDest);
        }

    if (SEM_ID_NULL != sem)
        {
        (void)semDelete (sem);
        }

    for (i = 0; i < cnt; i++)
        {
        if (NULL != pChan[i])
            {
            vxbDmaChanFree (pChan[i]);
            }
        }
    return ret;
    }

/*******************************************************************************
*
* tiEdma3TestChan - allocate a channel and test EDMA3 basic function
*
* This routine allocates a channel and tests EDMA3 basic function
*
* RETURNS: N/A
*
* ERRNO: N/A
*/

STATUS tiEdma3TestChan
    (
    UINT32  chanNum,
    UINT32  ctrlUnit
    )
    {
    int                     i;
    VXB_DMA_CHAN *          pChan = NULL;
    VXB_DMA_TX *            pTx;
    UINT32 *                pSrc    = NULL;
    UINT32 *                pDest   = NULL;
    UINT32                  size    = 1024;
    SEM_ID                  sem     = SEM_ID_NULL;
    VXB_DMA_SLAVE_CONFIG    config;
    STATUS                  ret = ERROR;

    if (chanNum >= 64)
        {
        printf("failure: chanNum >= 64 !\n");
        return ERROR;
        }

    bzero ((char *)&config, sizeof (VXB_DMA_SLAVE_CONFIG));

    sem = semBCreate (SEM_Q_FIFO, SEM_EMPTY);
    if (SEM_ID_NULL == sem)
        {
        printf("failure: semBCreate failed!\n");
        goto test_exit;
        }

    pSrc = (UINT32 *)cacheDmaMalloc (size);
    if (NULL == pSrc)
        {
        printf("failure: allocate pSrc failed!\n");
        goto test_exit;
        }

    pDest = (UINT32 *)cacheDmaMalloc (size);
    if (NULL == pDest)
        {
        printf("failure: allocate pDest failed!\n");
        goto test_exit;
        }

    printf("pSrc = 0x%x, pDest = 0x%x\n", pSrc, pDest);

    for (i = 0; i < (size / sizeof (UINT32)); i++)
        {
        *(pSrc + i) = i;
        }

    bzero ((char *)pDest, size);

    pChan = vxbDmaChanAllocAdvance ("TI EDMA3", ctrlUnit, chanNum, 0);
    if (NULL == pChan)
        {
        printf("failure: channel %d already used\n", chanNum);
        goto test_exit;
        }

    config.direction        = VXB_DMA_MEM_TO_MEM;
    config.destAddrWidth    = sizeof (UINT32);
    config.destMaxBurst     = size;
    config.dmaEvent         = -1;

    if (OK != vxbDmaChanConfig (pChan, &config))
        {
        printf("failure: vxbDmaChanConfig failed!\n");
        goto test_exit;
        }

    pTx = vxbDmaChanPreMemCpy (pChan, (VIRT_ADDR)pSrc, (VIRT_ADDR)pDest, size, 0);
    if (NULL == pTx)
        {
        printf("failure: vxbDmaChanPreMemCpy failed!\n");
        goto test_exit;
        }

    pTx->fn = (VXB_DMA_COMPLETE_FN)tiEdma3TestCallBack;
    pTx->pArg = (void *)sem;
    if (OK != vxbDmaChanStart (pTx))
        {
        printf("failure: vxbDmaChanStart failed!\n");
        goto test_exit;
        }

    (void)semTake (sem, WAIT_FOREVER);

    for (i = 0; i < (size / sizeof (UINT32)); i++)
        {
        if (*(pSrc + i) != *(pDest + i))
            {
            printf("failure: DmaTrans failed! "
                       "*(pSrc + i) = 0x%x, *(pDest + i) = 0x%x, i = %d\n",
                       *(pSrc + i), *(pDest + i), i);
            goto test_exit;
            }
        }

    ret = OK;

test_exit:
    if (NULL != pSrc)
        {
        (void)cacheDmaFree (pSrc);
        }

    if (NULL != pDest)
        {
        (void)cacheDmaFree (pDest);
        }

    if (SEM_ID_NULL != sem)
        {
        (void)semDelete (sem);
        }

    if (NULL != pChan)
        {
        vxbDmaChanFree (pChan);
        }
    return ret;
    }

STATUS edma_test(void)
{
    int i;

    printf("testing basic function for all of the 64 channels...\n");
    if(tiEdma3Test(64) != OK)
    {
        return ERROR;
    }
    printf("succeeded to test basic function for all of the 64 channels\n\n");

    for(i = 0; i < 64 ; i++)
    {
        printf("allocating channel %d and test basic function...\n", i);
        if(tiEdma3TestChan(i, 0) != OK)
        {
            printf("failure for channel %d ...\n\n", i);
        }
        else
        {
            printf("succeeded to test basic function for channel %d\n\n", i);
        }
    }
    return OK;
}

