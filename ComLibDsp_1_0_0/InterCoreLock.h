/*
 * Lock.h
 *
 *  Created on: 30.05.2021
 *      Author: hjouini_3P13713
 */

#ifndef INTERCORELOCK_H_
#define INTERCORELOCK_H_

void Icl_init(void);
void Icl_deinit(void);
void Icl_lock(uint32_t lock);
void Icl_unlock(uint32_t lock);


#endif /* INTERCORELOCK_H_ */
