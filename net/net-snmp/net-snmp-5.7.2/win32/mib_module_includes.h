
/* This file is automatically generated by configure.  Do not modify by hand. */

/*
 * The defines found in net-snmp/agent/mib_module_config.h
 * are used to include/exclude header files referenced here.
 */

#include "mibgroup/mibII.h"
#include "mibgroup/ucd_snmp.h"
#include "mibgroup/snmpv3mibs.h"
#include "mibgroup/notification.h"
#include "mibgroup/target.h"
#include "mibgroup/agent_mibs.h"

#ifdef USING_AGENTX_MODULE
#include "mibgroup/agentx.h"
#endif

#include "mibgroup/agent_mibs.h"
#include "mibgroup/utilities.h"

#ifdef USING_HOST_MODULE
#include "mibgroup/host.h"
#endif

#ifdef USING_RMON_MODULE
#include "mibgroup/Rmon.h"
#endif

#ifdef USING_DISMAN_EVENT_MODULE
#include "mibgroup/disman/event.h"
#endif

#ifdef USING_SMUX_MODULE
#include "mibgroup/smux.h"
#endif

#ifndef WIN32
#include "mibgroup/mibII/ipv6.h"
#endif

#include "mibgroup/mibII/system_mib.h"
#include "mibgroup/mibII/sysORTable.h"

#ifdef HAVE_WIN32_PLATFORM_SDK
#include "mibgroup/mibII/at.h"
#include "mibgroup/mibII/interfaces.h"
#include "mibgroup/mibII/tcp.h"
#include "mibgroup/mibII/icmp.h"
#include "mibgroup/mibII/ip.h"
#include "mibgroup/mibII/udp.h"
#include "mibgroup/mibII/tcpTable.h"
#include "mibgroup/mibII/ipAddr.h"
#include "mibgroup/mibII/udpTable.h"
#include "mibgroup/mibII/var_route.h"
#endif

#include "mibgroup/mibII/snmp_mib.h"
#include "mibgroup/mibII/vacm_vars.h"
#include "mibgroup/mibII/setSerialNo.h"

#ifdef USING_UCD_SNMP_MODULE
#include "mibgroup/ucd-snmp/memory.h"
#include "mibgroup/ucd-snmp/vmstat.h"
#include "mibgroup/ucd-snmp/proc.h"
#include "mibgroup/ucd-snmp/versioninfo.h"
#include "mibgroup/ucd-snmp/pass.h"
#include "mibgroup/ucd-snmp/pass_persist.h"
#include "mibgroup/ucd-snmp/disk.h"
#include "mibgroup/ucd-snmp/loadave.h"
#include "mibgroup/ucd-snmp/extensible.h"
#include "mibgroup/agent/extend.h"
#include "mibgroup/ucd-snmp/errormib.h"
#include "mibgroup/ucd-snmp/file.h"
#include "mibgroup/ucd-snmp/proxy.h"
#endif

#if HAVE_REGEX_H
#include "mibgroup/ucd-snmp/logmatch.h"
#endif

#include "mibgroup/snmpv3/snmpEngine.h"
#include "mibgroup/snmpv3/snmpMPDStats.h"
#include "mibgroup/snmpv3/usmStats.h"
#include "mibgroup/snmpv3/usmUser.h"
#include "mibgroup/notification/snmpNotifyTable.h"
#include "mibgroup/notification/snmpNotifyFilterProfileTable.h"
#include "mibgroup/snmp-notification-mib/snmpNotifyFilterTable.h"
#include "mibgroup/snmp-notification-mib/snmpNotifyFilterTable/snmpNotifyFilterTable.h"
#include "mibgroup/target/snmpTargetAddrEntry.h"
#include "mibgroup/target/snmpTargetParamsEntry.h"
#include "mibgroup/target/target.h"
#include "mibgroup/target/target_counters.h"
#include "mibgroup/agent/nsTransactionTable.h"
#include "mibgroup/agent/nsModuleTable.h"
#include "mibgroup/agent/nsDebug.h"
#include "mibgroup/agent/nsCache.h"
#include "mibgroup/agent/nsLogging.h"
#include "mibgroup/utilities/iquery.h"
#include "mibgroup/utilities/override.h"

#ifdef USING_HOST_MODULE
#include "mibgroup/host/hr_system.h"
#include "mibgroup/host/hr_storage.h"
#include "mibgroup/host/hr_device.h"
#include "mibgroup/host/hr_other.h"
#include "mibgroup/host/hr_proc.h"
#include "mibgroup/host/hr_network.h"
#include "mibgroup/host/hr_print.h"
#include "mibgroup/host/hr_disk.h"
#include "mibgroup/host/hr_partition.h"
#include "mibgroup/host/hr_filesys.h"
#include "mibgroup/host/hr_swrun.h"
#include "mibgroup/host/hr_swinst.h"
#endif

#ifdef USING_RMON_MODULE
#include "mibgroup/Rmon/rows.h"
#include "mibgroup/Rmon/agutil.h"
#include "mibgroup/Rmon/statistics.h"
#include "mibgroup/Rmon/alarm.h"
#include "mibgroup/Rmon/history.h"
#include "mibgroup/Rmon/event.h"
#endif

#ifdef USING_DISMAN_EVENT_MODULE
#include "mibgroup/disman/event/mteEventConf.h"
#include "mibgroup/disman/event/mteEvent.h"
#include "mibgroup/disman/event/mteEventNotificationTable.h"
#include "mibgroup/disman/event/mteEventSetTable.h"
#include "mibgroup/disman/event/mteEventTable.h"
#include "mibgroup/disman/event/mteObjectsConf.h"
#include "mibgroup/disman/event/mteObjects.h"
#include "mibgroup/disman/event/mteObjectsTable.h"
#include "mibgroup/disman/event/mteScalars.h"
#include "mibgroup/disman/event/mteTriggerBooleanTable.h"
#include "mibgroup/disman/event/mteTriggerConf.h"
#include "mibgroup/disman/event/mteTriggerDeltaTable.h"
#include "mibgroup/disman/event/mteTriggerExistenceTable.h"
#include "mibgroup/disman/event/mteTrigger.h"
#include "mibgroup/disman/event/mteTriggerTable.h"
#include "mibgroup/disman/event/mteTriggerThresholdTable.h"
#endif

#ifdef USING_SMUX_MODULE
#include "mibgroup/smux/smux.h"
#endif

#include "mibgroup/mibII/route_write.h"
#include "mibgroup/util_funcs.h"
#include "mibgroup/mibII/vacm_context.h"
#include "mibgroup/mibII/vacm_conf.h"
#include "mibgroup/utilities/execute.h"
#include "mibgroup/header_complex.h"

#ifdef USING_AGENTX_MODULE
#include "mibgroup/agentx/master.h"
#include "mibgroup/agentx/subagent.h"
#include "mibgroup/agentx/protocol.h"
#include "mibgroup/agentx/client.h"
#include "mibgroup/agentx/master_admin.h"
#include "mibgroup/agentx/agentx_config.h"
#endif

#ifdef USING_EXAMPLES_EXAMPLE_MODULE
#include "mibgroup/examples/example.h"
#endif

#ifdef USING_EXAMPLES_UCDDEMOPUBLIC_MODULE
#include "mibgroup/examples/ucdDemoPublic.h"
#endif

#ifdef USING_WINEXTDLL_MODULE
#include "mibgroup/winExtDLL.h"
#endif
