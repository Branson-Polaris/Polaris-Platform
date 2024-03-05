/* Automatically generated file by prj_vsb.tcl: do not edit */

Layer Layer::ARM {
}

Layer Layer::BRANSON_DRV_SR2107 {
}

Layer Layer::CONTAINER {
}

Layer Layer::CONTAINER_EXAMPLES {
}

Layer Layer::CONTAINER_MANAGER {
}

Layer Layer::CONTAINER_RUNTIME {
}

Layer Layer::CORE {
}

Layer Layer::CORE_CUSTOM {
}

Layer Layer::CORE_RTP {
}

Layer Layer::CORE_SAFETY {
}

Layer Layer::CORE_SYSCALLS {
}

Layer Layer::CPLUS_KERNEL {
}

Layer Layer::FDT {
}

Layer Layer::IA {
}

Layer Layer::INTRINSICS_COMMON {
}

Layer Layer::INTRINSICS_GNU {
}

Layer Layer::INTRINSICS_LLVM {
}

Layer Layer::LIBCPLUS_STD {
}

Layer Layer::LIBC_BOOT {
}

Layer Layer::LIBC_STD {
}

Layer Layer::PPC {
}

Layer Layer::PPC_MATH_FSLE500V2 {
}

Layer Layer::PPC_PPCMATH {
}

Layer Layer::PROFILES {
}

Layer Layer::PSCI {
}

Layer Layer::RISCV {
}

Layer Layer::SERVICE {
}

Layer Layer::SERVICE_EPOLL {
}

Layer Layer::SERVICE_ERF {
}

Layer Layer::SERVICE_JOBQUEUE {
}

Layer Layer::SERVICE_REMOTEPROC {
}

Layer Layer::SERVICE_RPC {
}

Layer Layer::SERVICE_RPMSG {
}

Layer Layer::SERVICE_SOCKET {
}

Layer Layer::SERVICE_UN {
}

Layer Layer::UTILS {
}

Layer Layer::UTILS_BOOTAPP {
}

Layer Layer::UTILS_DEPLOY {
}

Layer Layer::UTILS_LOADER {
}

Layer Layer::UTILS_OSTOOLS {
}

Layer Layer::UTILS_RBUFF {
}

Layer Layer::UTILS_RUST {
}

Layer Layer::UTILS_SHELL {
}

Layer Layer::UTILS_UNIX {
}

Layer Layer::UTILS_UTF {
}

Layer Layer::UTILS_UUID {
}

Layer Layer::UTILS_WRCC {
}

Layer Layer::VIP_PROFILES {
}

Layer Layer::VXBUS {
}

Layer Layer::VXBUS_DRV {
}

Layer Layer::VXSIM {
}

Feature COREOS
{
 NAME   COREOS feature
 SYNOPSIS   COREOS layers
 HELP   This feature contains all layers that provide COREOS libraries.
 LAYERS   \
   Layer::ARM \
   Layer::BRANSON_DRV_SR2107 \
   Layer::CONTAINER \
   Layer::CONTAINER_EXAMPLES \
   Layer::CONTAINER_MANAGER \
   Layer::CONTAINER_RUNTIME \
   Layer::CORE \
   Layer::CORE_CUSTOM \
   Layer::CORE_RTP \
   Layer::CORE_SAFETY \
   Layer::CORE_SYSCALLS \
   Layer::CPLUS_KERNEL \
   Layer::FDT \
   Layer::IA \
   Layer::INTRINSICS_COMMON \
   Layer::INTRINSICS_GNU \
   Layer::INTRINSICS_LLVM \
   Layer::LIBCPLUS_STD \
   Layer::LIBC_BOOT \
   Layer::LIBC_STD \
   Layer::PPC \
   Layer::PPC_MATH_FSLE500V2 \
   Layer::PPC_PPCMATH \
   Layer::PROFILES \
   Layer::PSCI \
   Layer::RISCV \
   Layer::SERVICE \
   Layer::SERVICE_EPOLL \
   Layer::SERVICE_ERF \
   Layer::SERVICE_JOBQUEUE \
   Layer::SERVICE_REMOTEPROC \
   Layer::SERVICE_RPC \
   Layer::SERVICE_RPMSG \
   Layer::SERVICE_SOCKET \
   Layer::SERVICE_UN \
   Layer::UTILS \
   Layer::UTILS_BOOTAPP \
   Layer::UTILS_DEPLOY \
   Layer::UTILS_LOADER \
   Layer::UTILS_OSTOOLS \
   Layer::UTILS_RBUFF \
   Layer::UTILS_RUST \
   Layer::UTILS_SHELL \
   Layer::UTILS_UNIX \
   Layer::UTILS_UTF \
   Layer::UTILS_UUID \
   Layer::UTILS_WRCC \
   Layer::VIP_PROFILES \
   Layer::VXBUS \
   Layer::VXBUS_DRV \
   Layer::VXSIM \

}

Layer Layer::BCM2711 {
}

Layer Layer::BCM2837 {
}

Layer Layer::FSL_IMX {
}

Layer Layer::FSL_KINETIS {
}

Layer Layer::FSL_PQ2 {
}

Layer Layer::FSL_QORIQ {
}

Layer Layer::FSL_S32 {
}

Layer Layer::FSL_VYBRID {
}

Layer Layer::ITL_SOC_ARRIA10 {
}

Layer Layer::ITL_SOC_COMMON {
}

Layer Layer::ITL_SOC_CYCLONE5 {
}

Layer Layer::ITL_X86_COMMON {
}

Layer Layer::MCHP_PFSOC {
}

Layer Layer::MV_64360 {
}

Layer Layer::PSL_XLNX_VERSAL {
}

Layer Layer::QSP {
}

Layer Layer::RENESAS_COMMON {
}

Layer Layer::RENESAS_RCAR {
}

Layer Layer::RENESAS_RZ {
}

Layer Layer::RENESAS_RZ_G2 {
}

Layer Layer::SIFIVE_RISCV {
}

Layer Layer::TI_FIRMWARE {
}

Layer Layer::TI_KEYSTONE {
}

Layer Layer::TI_SITARA {
}

Layer Layer::XEN {
}

Layer Layer::XLNX_COMMON {
}

Layer Layer::XLNX_ZYNQ {
}

Feature PSL
{
 NAME   PSL feature
 SYNOPSIS   Platform Specific Layers
 HELP   This feature contains all layers that provide platform specific libraries.
 LAYERS   \
   Layer::BCM2711 \
   Layer::BCM2837 \
   Layer::FSL_IMX \
   Layer::FSL_KINETIS \
   Layer::FSL_PQ2 \
   Layer::FSL_QORIQ \
   Layer::FSL_S32 \
   Layer::FSL_VYBRID \
   Layer::ITL_SOC_ARRIA10 \
   Layer::ITL_SOC_COMMON \
   Layer::ITL_SOC_CYCLONE5 \
   Layer::ITL_X86_COMMON \
   Layer::MCHP_PFSOC \
   Layer::MV_64360 \
   Layer::PSL_XLNX_VERSAL \
   Layer::QSP \
   Layer::RENESAS_COMMON \
   Layer::RENESAS_RCAR \
   Layer::RENESAS_RZ \
   Layer::RENESAS_RZ_G2 \
   Layer::SIFIVE_RISCV \
   Layer::TI_FIRMWARE \
   Layer::TI_KEYSTONE \
   Layer::TI_SITARA \
   Layer::XEN \
   Layer::XLNX_COMMON \
   Layer::XLNX_ZYNQ \

}

Layer Layer::DEBUG {
}

Layer Layer::DEBUG_SYSTEMVIEWER {
}

Layer Layer::RTTOOLS {
}

Layer Layer::RTTOOLS_DEBUG_AGENT {
}

Layer Layer::RTTOOLS_RUNTIME_ANALYSIS {
}

Layer Layer::RTTOOLS_STOP_MODE_DEBUG_AGENT {
}

Layer Layer::RTTOOLS_SYSTEMVIEWER_AGENT {
}

Feature DEBUG_ANALYSIS
{
 NAME   DEBUG_ANALYSIS feature
 SYNOPSIS   DEBUG_ANALYSIS layers
 HELP   This feature contains all layers that provide DEBUG and DEBUG_ANALYSIS libraries.
 LAYERS   \
   Layer::DEBUG \
   Layer::DEBUG_SYSTEMVIEWER \
   Layer::RTTOOLS \
   Layer::RTTOOLS_DEBUG_AGENT \
   Layer::RTTOOLS_RUNTIME_ANALYSIS \
   Layer::RTTOOLS_STOP_MODE_DEBUG_AGENT \
   Layer::RTTOOLS_SYSTEMVIEWER_AGENT \

}

Feature HDC
{
 NAME   HDC feature
 SYNOPSIS   Helix Device Cloud Agent
 HELP   This feature contains the layers for the Helix Device Cloud Agent.
 LAYERS   \

}

Layer Layer::CAN {
}

Layer Layer::IEEE1394 {
}

Layer Layer::USB {
}

Layer Layer::USB_CDNSUSB3 {
}

Layer Layer::USB_CTLR {
}

Layer Layer::USB_DWC2DR {
}

Layer Layer::USB_EHCI {
}

Layer Layer::USB_FSLDR {
}

Layer Layer::USB_HOST {
}

Layer Layer::USB_MHDRC {
}

Layer Layer::USB_MSC {
}

Layer Layer::USB_NET {
}

Layer Layer::USB_NETWORK {
}

Layer Layer::USB_OHCI {
}

Layer Layer::USB_OTG {
}

Layer Layer::USB_PCHUDC {
}

Layer Layer::USB_PHY {
}

Layer Layer::USB_PLX {
}

Layer Layer::USB_RZN1 {
}

Layer Layer::USB_STORAGE {
}

Layer Layer::USB_TARGET {
}

Layer Layer::USB_TOUCHSCREEN {
}

Layer Layer::USB_TYPEC {
}

Layer Layer::USB_UHCI {
}

Layer Layer::USB_USBDWC3 {
}

Layer Layer::USB_XHCI {
}

Feature CONNECTIVITY
{
 NAME   CONNECTIVITY feature
 SYNOPSIS   CONNECTIVITY layers
 HELP   This feature contains all layers that provide CONNECTIVITY libraries.
 LAYERS   \
   Layer::CAN \
   Layer::IEEE1394 \
   Layer::USB \
   Layer::USB_CDNSUSB3 \
   Layer::USB_CTLR \
   Layer::USB_DWC2DR \
   Layer::USB_EHCI \
   Layer::USB_FSLDR \
   Layer::USB_HOST \
   Layer::USB_MHDRC \
   Layer::USB_MSC \
   Layer::USB_NET \
   Layer::USB_NETWORK \
   Layer::USB_OHCI \
   Layer::USB_OTG \
   Layer::USB_PCHUDC \
   Layer::USB_PHY \
   Layer::USB_PLX \
   Layer::USB_RZN1 \
   Layer::USB_STORAGE \
   Layer::USB_TARGET \
   Layer::USB_TOUCHSCREEN \
   Layer::USB_TYPEC \
   Layer::USB_UHCI \
   Layer::USB_USBDWC3 \
   Layer::USB_XHCI \

}

Layer Layer::BRANSON_HTTP {
}

Layer Layer::BRANSON_WEBSERVICES {
}

Layer Layer::END {
}

Layer Layer::GPTP {
}

Layer Layer::IPNET_8021X {
}

Layer Layer::IPNET_AAA {
}

Layer Layer::IPNET_COREIP {
}

Layer Layer::IPNET_DHCP {
}

Layer Layer::IPNET_DHCP_CLIENT {
}

Layer Layer::IPNET_DHCP_CLIENT6 {
}

Layer Layer::IPNET_DHCP_RELAY {
}

Layer Layer::IPNET_DHCP_SERVER {
}

Layer Layer::IPNET_DHCP_SERVER6 {
}

Layer Layer::IPNET_DNSC {
}

Layer Layer::IPNET_EAP {
}

Layer Layer::IPNET_FIREWALL {
}

Layer Layer::IPNET_FTP {
}

Layer Layer::IPNET_IPSECIKE {
}

Layer Layer::IPNET_IPSECIKE_GDOI {
}

Layer Layer::IPNET_IPSECIKE_IKE {
}

Layer Layer::IPNET_LINKPROTO {
}

Layer Layer::IPNET_QOS {
}

Layer Layer::IPNET_ROUTEPROTO {
}

Layer Layer::IPNET_SNTP {
}

Layer Layer::IPNET_SSH {
}

Layer Layer::IPNET_TFTP {
}

Layer Layer::IPNET_USRSPACE {
}

Layer Layer::IPNET_VRRP {
}

Layer Layer::LIBCURL {
}

Layer Layer::MIB2 {
}

Layer Layer::NET_BASE {
}

Layer Layer::NTP {
}

Layer Layer::PTP {
}

Layer Layer::RTNET {
}

Layer Layer::SNMP {
}

Layer Layer::TSN {
}

Layer Layer::WEBCLI {
}

Layer Layer::WEBCLI_CLIDEMO {
}

Layer Layer::WEBCLI_HTTP {
}

Layer Layer::WEBCLI_MIBWAY {
}

Layer Layer::WEBCLI_WEBCLIDEMO {
}

Layer Layer::WEBCLI_WEBDEMO {
}

Feature NETWORKING
{
 NAME   NETWORKING feature
 SYNOPSIS   NETWORKING layers
 HELP   This feature contains all layers that provide NETWORKING libraries.
 LAYERS   \
   Layer::BRANSON_HTTP \
   Layer::BRANSON_WEBSERVICES \
   Layer::END \
   Layer::GPTP \
   Layer::IPNET_8021X \
   Layer::IPNET_AAA \
   Layer::IPNET_COREIP \
   Layer::IPNET_DHCP \
   Layer::IPNET_DHCP_CLIENT \
   Layer::IPNET_DHCP_CLIENT6 \
   Layer::IPNET_DHCP_RELAY \
   Layer::IPNET_DHCP_SERVER \
   Layer::IPNET_DHCP_SERVER6 \
   Layer::IPNET_DNSC \
   Layer::IPNET_EAP \
   Layer::IPNET_FIREWALL \
   Layer::IPNET_FTP \
   Layer::IPNET_IPSECIKE \
   Layer::IPNET_IPSECIKE_GDOI \
   Layer::IPNET_IPSECIKE_IKE \
   Layer::IPNET_LINKPROTO \
   Layer::IPNET_QOS \
   Layer::IPNET_ROUTEPROTO \
   Layer::IPNET_SNTP \
   Layer::IPNET_SSH \
   Layer::IPNET_TFTP \
   Layer::IPNET_USRSPACE \
   Layer::IPNET_VRRP \
   Layer::LIBCURL \
   Layer::MIB2 \
   Layer::NET_BASE \
   Layer::NTP \
   Layer::PTP \
   Layer::RTNET \
   Layer::SNMP \
   Layer::TSN \
   Layer::WEBCLI \
   Layer::WEBCLI_CLIDEMO \
   Layer::WEBCLI_HTTP \
   Layer::WEBCLI_MIBWAY \
   Layer::WEBCLI_WEBCLIDEMO \
   Layer::WEBCLI_WEBDEMO \

}

Feature NOT_DEFINED
{
 NAME   NOT_DEFINED feature
 SYNOPSIS   NOT_DEFINED layers
 HELP   This feature contains all layers that do not have the FEATURE keyword set.
 LAYERS   \

}

Layer Layer::CRYPTOMISC {
}

Layer Layer::CRYPTOMISC_IAF {
}

Layer Layer::CRYPTOMISC_IPFREESCALE {
}

Layer Layer::CRYPTOMISC_IPHWCRYPTO {
}

Layer Layer::CRYPTOMISC_TPM {
}

Layer Layer::DISK_ENCRYPTION {
}

Layer Layer::LDAPC {
}

Layer Layer::OPENSSL {
}

Layer Layer::OPENSSL_FIPS {
}

Layer Layer::OP_TEE {
}

Layer Layer::OP_TEE_DEMO {
}

Layer Layer::SECURE_LOADER {
}

Layer Layer::SECURITY_EVENT {
}

Layer Layer::SECURITY_MISC {
}

Layer Layer::SECURITY_MISC_SCEP {
}

Layer Layer::SECURITY_MISC_SEC_CRYPTO {
}

Layer Layer::SECURITY_MISC_SEC_HASH {
}

Layer Layer::TPM2_TSS {
}

Layer Layer::USER_MANAGEMENT {
}

Layer Layer::USER_MANAGEMENT_LDAP {
}

Layer Layer::USER_MANAGEMENT_POLICY {
}

Layer Layer::USER_MANAGEMENT_USER_PRIVILEGES {
}

Feature SECURITY
{
 NAME   SECURITY feature
 SYNOPSIS   SECURITY layers
 HELP   This feature contains all layers that provide SECURITY libraries.
 LAYERS   \
   Layer::CRYPTOMISC \
   Layer::CRYPTOMISC_IAF \
   Layer::CRYPTOMISC_IPFREESCALE \
   Layer::CRYPTOMISC_IPHWCRYPTO \
   Layer::CRYPTOMISC_TPM \
   Layer::DISK_ENCRYPTION \
   Layer::LDAPC \
   Layer::OPENSSL \
   Layer::OPENSSL_FIPS \
   Layer::OP_TEE \
   Layer::OP_TEE_DEMO \
   Layer::SECURE_LOADER \
   Layer::SECURITY_EVENT \
   Layer::SECURITY_MISC \
   Layer::SECURITY_MISC_SCEP \
   Layer::SECURITY_MISC_SEC_CRYPTO \
   Layer::SECURITY_MISC_SEC_HASH \
   Layer::TPM2_TSS \
   Layer::USER_MANAGEMENT \
   Layer::USER_MANAGEMENT_LDAP \
   Layer::USER_MANAGEMENT_POLICY \
   Layer::USER_MANAGEMENT_USER_PRIVILEGES \

}

Layer Layer::BDM {
}

Layer Layer::BDM_FLASH {
}

Layer Layer::BDM_LOOPFS {
}

Layer Layer::BDM_NVME {
}

Layer Layer::BDM_NVRAM {
}

Layer Layer::BDM_SATA {
}

Layer Layer::BDM_SDMMC {
}

Layer Layer::BDM_SIM {
}

Layer Layer::FS {
}

Layer Layer::FS_CDROMFS {
}

Layer Layer::FS_DOSFS {
}

Layer Layer::FS_HRFS {
}

Layer Layer::FS_NFS {
}

Layer Layer::FS_OVERLAY {
}

Layer Layer::FS_ROMFS {
}

Layer Layer::FS_UTIL {
}

Layer Layer::FS_VRFS {
}

Layer Layer::TCPLAY {
}

Feature STORAGE
{
 NAME   STORAGE feature
 SYNOPSIS   STORAGE layers
 HELP   This feature contains all layers that provide STORAGE libraries.
 LAYERS   \
   Layer::BDM \
   Layer::BDM_FLASH \
   Layer::BDM_LOOPFS \
   Layer::BDM_NVME \
   Layer::BDM_NVRAM \
   Layer::BDM_SATA \
   Layer::BDM_SDMMC \
   Layer::BDM_SIM \
   Layer::FS \
   Layer::FS_CDROMFS \
   Layer::FS_DOSFS \
   Layer::FS_HRFS \
   Layer::FS_NFS \
   Layer::FS_OVERLAY \
   Layer::FS_ROMFS \
   Layer::FS_UTIL \
   Layer::FS_VRFS \
   Layer::TCPLAY \

}

Feature TEST
{
 NAME   TEST feature
 SYNOPSIS   TEST layers
 HELP   This feature contains all layers that provide TEST libraries.
 LAYERS   \

}

Layer Layer::AUDIO {
}

Layer Layer::BRANSON_TIDSSFB {
}

Layer Layer::DRM {
}

Layer Layer::EVDEV {
}

Layer Layer::FBDEV {
}

Layer Layer::FREETYPE2 {
}

Layer Layer::GPUDEV {
}

Layer Layer::GPUDEV_FSLVIVGPU {
}

Layer Layer::GPUDEV_NXPVIVGPU {
}

Layer Layer::GPUDEV_RCAR_DU {
}

Layer Layer::ITLI915 {
}

Layer Layer::KHRONOS {
}

Layer Layer::LIBDRM {
}

Layer Layer::LIBJPEG {
}

Layer Layer::LIBPNG {
}

Layer Layer::MESA {
}

Layer Layer::RASTER {
}

Layer Layer::RASTER_VG {
}

Layer Layer::SDL {
}

Layer Layer::TILCON {
}

Feature MULTIMEDIA
{
 NAME   MULTIMEDIA feature
 SYNOPSIS   MULTIMEDIA layers
 HELP   This feature contains all layers that provide MULTIMEDIA libraries.
 LAYERS   \
   Layer::AUDIO \
   Layer::BRANSON_TIDSSFB \
   Layer::DRM \
   Layer::EVDEV \
   Layer::FBDEV \
   Layer::FREETYPE2 \
   Layer::GPUDEV \
   Layer::GPUDEV_FSLVIVGPU \
   Layer::GPUDEV_NXPVIVGPU \
   Layer::GPUDEV_RCAR_DU \
   Layer::ITLI915 \
   Layer::KHRONOS \
   Layer::LIBDRM \
   Layer::LIBJPEG \
   Layer::LIBPNG \
   Layer::MESA \
   Layer::RASTER \
   Layer::RASTER_VG \
   Layer::SDL \
   Layer::TILCON \

}

Layer Layer::GUEST_SUPPORT_VX7 {
}

Layer Layer::GUEST_SUPPORT_VX7_BENCHMARKS {
}

Layer Layer::GUEST_SUPPORT_VX7_DSS {
}

Layer Layer::GUEST_SUPPORT_VX7_HVIF {
}

Layer Layer::GUEST_SUPPORT_VX7_SAFE {
}

Layer Layer::GUEST_SUPPORT_VX7_SAFE_APEX {
}

Layer Layer::GUEST_SUPPORT_VX7_SAFE_HM {
}

Layer Layer::GUEST_SUPPORT_VX7_SAFE_HVIF {
}

Layer Layer::GUEST_SUPPORT_VX7_SAFE_MPFS {
}

Layer Layer::GUEST_SUPPORT_VX7_SAFE_SAFEIPC {
}

Layer Layer::GUEST_SUPPORT_VX7_SAFE_SOCKET {
}

Layer Layer::GUEST_SUPPORT_VX7_SHMEM {
}

Layer Layer::GUEST_SUPPORT_VX7_SYSTEMVIEWER {
}

Layer Layer::GUEST_SUPPORT_VX7_THROTTLE {
}

Layer Layer::GUEST_SUPPORT_VX7_VIRTIO {
}

Layer Layer::GUEST_SUPPORT_VX7_VNIC {
}

Feature VIRTUALIZATION_GUEST
{
 NAME   VIRTUALIZATION_GUEST feature
 SYNOPSIS   GUEST SUPPORT VIRTUALIZATION layers
 HELP   This feature contains all layers that provide VIRTUALIZATION libraries for guest support.
 LAYERS   \
   Layer::GUEST_SUPPORT_VX7 \
   Layer::GUEST_SUPPORT_VX7_BENCHMARKS \
   Layer::GUEST_SUPPORT_VX7_DSS \
   Layer::GUEST_SUPPORT_VX7_HVIF \
   Layer::GUEST_SUPPORT_VX7_SAFE \
   Layer::GUEST_SUPPORT_VX7_SAFE_APEX \
   Layer::GUEST_SUPPORT_VX7_SAFE_HM \
   Layer::GUEST_SUPPORT_VX7_SAFE_HVIF \
   Layer::GUEST_SUPPORT_VX7_SAFE_MPFS \
   Layer::GUEST_SUPPORT_VX7_SAFE_SAFEIPC \
   Layer::GUEST_SUPPORT_VX7_SAFE_SOCKET \
   Layer::GUEST_SUPPORT_VX7_SHMEM \
   Layer::GUEST_SUPPORT_VX7_SYSTEMVIEWER \
   Layer::GUEST_SUPPORT_VX7_THROTTLE \
   Layer::GUEST_SUPPORT_VX7_VIRTIO \
   Layer::GUEST_SUPPORT_VX7_VNIC \

}

Layer Layer::ACPI {
}

Layer Layer::BOOST {
}

Layer Layer::BZIP2 {
}

Layer Layer::CIVETWEB {
}

Layer Layer::CJSON {
}

Layer Layer::EXPAT {
}

Layer Layer::GSOAP {
}

Layer Layer::ICU {
}

Layer Layer::INTEL_IPP {
}

Layer Layer::INTEL_MKL {
}

Layer Layer::JANSSON {
}

Layer Layer::LIBARCHIVE {
}

Layer Layer::LIBFFI {
}

Layer Layer::LZMA {
}

Layer Layer::MIMALLOC {
}

Layer Layer::MOSQUITTO {
}

Layer Layer::ONETBB {
}

Layer Layer::OPEN62541 {
}

Layer Layer::OPENCV {
}

Layer Layer::OPENMP {
}

Layer Layer::PARG {
}

Layer Layer::PYTHON {
}

Layer Layer::PYTHON_CYTHON {
}

Layer Layer::PYTHON_DATEUTIL {
}

Layer Layer::PYTHON_NUMPY {
}

Layer Layer::PYTHON_PANDAS {
}

Layer Layer::PYTHON_PYTZ {
}

Layer Layer::PYTHON_SIX {
}

Layer Layer::SQLITE {
}

Layer Layer::TENSORFLOW_LITE {
}

Layer Layer::UZLIB {
}

Layer Layer::VI_EDITOR {
}

Layer Layer::XRT {
}

Layer Layer::ZLIB {
}

Feature OPEN_SOURCE
{
 NAME   OPEN_SOURCE feature
 SYNOPSIS   Open Source recipe layers
 HELP   This feature provides layers enabling third party code from the open source community to be used in VxWorks.
 LAYERS   \
   Layer::ACPI \
   Layer::BOOST \
   Layer::BZIP2 \
   Layer::CIVETWEB \
   Layer::CJSON \
   Layer::EXPAT \
   Layer::GSOAP \
   Layer::ICU \
   Layer::INTEL_IPP \
   Layer::INTEL_MKL \
   Layer::JANSSON \
   Layer::LIBARCHIVE \
   Layer::LIBFFI \
   Layer::LZMA \
   Layer::MIMALLOC \
   Layer::MOSQUITTO \
   Layer::ONETBB \
   Layer::OPEN62541 \
   Layer::OPENCV \
   Layer::OPENMP \
   Layer::PARG \
   Layer::PYTHON \
   Layer::PYTHON_CYTHON \
   Layer::PYTHON_DATEUTIL \
   Layer::PYTHON_NUMPY \
   Layer::PYTHON_PANDAS \
   Layer::PYTHON_PYTZ \
   Layer::PYTHON_SIX \
   Layer::SQLITE \
   Layer::TENSORFLOW_LITE \
   Layer::UZLIB \
   Layer::VI_EDITOR \
   Layer::XRT \
   Layer::ZLIB \

}

Feature VIRTUALIZATION
{
 NAME   VIRTUALIZATION feature
 SYNOPSIS   VIRTUALIZATION layers
 HELP   This feature contains all layers that provide VIRTUALIZATION libraries.
 LAYERS   \

}

