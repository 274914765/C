#ifndef _ASM_SPARC64_TOPOLOGY_H
#define _ASM_SPARC64_TOPOLOGY_H

#ifdef CONFIG_NUMA

#include <asm/mmzone.h>

static inline int cpu_to_node(int cpu)
{
    return numa_cpu_lookup_table[cpu];
}

#define parent_node(node)    (node)

static inline cpumask_t node_to_cpumask(int node)
{
    return numa_cpumask_lookup_table[node];
}

/* Returns a pointer to the cpumask of CPUs on Node 'node'. */
#define node_to_cpumask_ptr(v, node)        \
        cpumask_t *v = &(numa_cpumask_lookup_table[node])

#define node_to_cpumask_ptr_next(v, node)    \
               v = &(numa_cpumask_lookup_table[node])

static inline int node_to_first_cpu(int node)
{
    cpumask_t tmp;
    tmp = node_to_cpumask(node);
    return first_cpu(tmp);
}

struct pci_bus;
#ifdef CONFIG_PCI
extern int pcibus_to_node(struct pci_bus *pbus);
#else
static inline int pcibus_to_node(struct pci_bus *pbus)
{
    return -1;
}
#endif

#define pcibus_to_cpumask(bus)    \
    (pcibus_to_node(bus) == -1 ? \
     CPU_MASK_ALL : \
     node_to_cpumask(pcibus_to_node(bus)))

#define SD_NODE_INIT (struct sched_domain) {        \
    .min_interval        = 8,            \
    .max_interval        = 32,            \
    .busy_factor        = 32,            \
    .imbalance_pct        = 125,            \
    .cache_nice_tries    = 2,            \
    .busy_idx        = 3,            \
    .idle_idx        = 2,            \
    .newidle_idx        = 0,             \
    .wake_idx        = 1,            \
    .forkexec_idx        = 1,            \
    .flags            = SD_LOAD_BALANCE    \
                | SD_BALANCE_FORK    \
                | SD_BALANCE_EXEC    \
                | SD_SERIALIZE        \
                | SD_WAKE_BALANCE,    \
    .last_balance        = jiffies,        \
    .balance_interval    = 1,            \
}

#else /* CONFIG_NUMA */

#include <asm-generic/topology.h>

#endif /* !(CONFIG_NUMA) */

#ifdef CONFIG_SMP
#define topology_physical_package_id(cpu)    (cpu_data(cpu).proc_id)
#define topology_core_id(cpu)            (cpu_data(cpu).core_id)
#define topology_core_siblings(cpu)        (cpu_core_map[cpu])
#define topology_thread_siblings(cpu)        (per_cpu(cpu_sibling_map, cpu))
#define mc_capable()                (sparc64_multi_core)
#define smt_capable()                (sparc64_multi_core)
#endif /* CONFIG_SMP */

#define cpu_coregroup_map(cpu)            (cpu_core_map[cpu])

#endif /* _ASM_SPARC64_TOPOLOGY_H */
