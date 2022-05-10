#include "cache.h"

uint32_t CACHE::find_victim(uint32_t cpu, uint64_t instr_id, uint32_t set, const BLOCK *current_set, uint64_t ip, uint64_t full_addr, uint32_t type)
{
    // baseline LRU replacement policy for other caches
    return lru_victim_notLLC(cpu, instr_id, set, current_set, ip, full_addr, type);
}

void CACHE::update_replacement_state(uint32_t cpu, uint32_t set, uint32_t way, uint64_t full_addr, uint64_t ip, uint64_t victim_addr, uint32_t type, uint8_t hit)
{
    if (type == WRITEBACK)
    {
        if (hit) // wrietback hit does not update LRU state
            return;
    }

    return lru_update_notLLC(set, way);
}
uint32_t NUM_WAY_t = 0, NUM_WAY_end = 0;
uint32_t CACHE::lru_victim(uint32_t cpu, uint64_t instr_id, uint32_t set, const BLOCK *current_set, uint64_t ip, uint64_t full_addr, uint32_t type)
{
    uint32_t way = 0;
    if (cpu == 0)
    {
        NUM_WAY_t = 0;
        NUM_WAY_end = 15;
        for (way = NUM_WAY_t; way < NUM_WAY_end; way++)
            block[set][way].cpu = cpu;
    }
    if (cpu == 1)
    {
        NUM_WAY_t = 15;
        NUM_WAY_end = NUM_WAY;
        for (way = NUM_WAY_t; way < NUM_WAY_end; way++)
            block[set][way].cpu = cpu;
    }
    // fill invalid line first
    for (way = 0; way < NUM_WAY; way++)
    {
        if (block[set][way].cpu == cpu and block[set][way].valid == false)
        {

            DP(if (warmup_complete[cpu]) {
            cout << "[" << NAME << "] " << __func__ << " instr_id: " << instr_id << " invalid set: " << set << " way: " << way;
            cout << hex << " address: " << (full_addr>>LOG2_BLOCK_SIZE) << " victim address: " << block[set][way].address << " data: " << block[set][way].data;
            cout << dec << " lru: " << block[set][way].lru << endl; });

            break;
        }
    }

    // LRU victim
    if (way == NUM_WAY)
    {
        for (way = 0; way < NUM_WAY; way++)
        {
            if (block[set][way].cpu == cpu and block[set][way].lru == (NUM_WAY_end - NUM_WAY_t) - 1)
            {

                DP(if (warmup_complete[cpu]) {
                cout << "[" << NAME << "] " << __func__ << " instr_id: " << instr_id << " replace set: " << set << " way: " << way;
                cout << hex << " address: " << (full_addr>>LOG2_BLOCK_SIZE) << " victim address: " << block[set][way].address << " data: " << block[set][way].data;
                cout << dec << " lru: " << block[set][way].lru << endl; });

                break;
            }
        }
    }

    if (way == NUM_WAY)
    {
        cout << "LRU values : " << endl;
        for (way = 0; way < NUM_WAY; way++)
            cout << block[set][way].cpu << " : " << block[set][way].lru << endl;
        cerr << "[" << NAME << "] " << __func__ << " no victim! set: " << set << endl;
        cerr << "[" << cpu << "] " << __func__ << " no victim! set: " << cpu << endl;
        cerr << "[" << NUM_WAY_t << "] " << __func__ << " no victim! set: " << NUM_WAY_t << endl;
        cerr << "[" << NUM_WAY_end << "] " << __func__ << " no victim! set: " << NUM_WAY_end << endl;
        assert(0);
    }
    if (way == 16)
        cout << "way=16" << way << endl;
    return way;
}
uint32_t CACHE::lru_victim_notLLC(uint32_t cpu, uint64_t instr_id, uint32_t set, const BLOCK *current_set, uint64_t ip, uint64_t full_addr, uint32_t type)
{
    uint32_t way = 0;

    // fill invalid line first
    for (way = 0; way < NUM_WAY; way++)
    {
        if (block[set][way].valid == false)
        {

            DP(if (warmup_complete[cpu]) {
            cout << "[" << NAME << "] " << __func__ << " instr_id: " << instr_id << " invalid set: " << set << " way: " << way;
            cout << hex << " address: " << (full_addr>>LOG2_BLOCK_SIZE) << " victim address: " << block[set][way].address << " data: " << block[set][way].data;
            cout << dec << " lru: " << block[set][way].lru << endl; });

            break;
        }
    }

    // LRU victim
    if (way == NUM_WAY)
    {
        for (way = 0; way < NUM_WAY; way++)
        {
            if (block[set][way].lru == NUM_WAY - 1)
            {

                DP(if (warmup_complete[cpu]) {
                cout << "[" << NAME << "] " << __func__ << " instr_id: " << instr_id << " replace set: " << set << " way: " << way;
                cout << hex << " address: " << (full_addr>>LOG2_BLOCK_SIZE) << " victim address: " << block[set][way].address << " data: " << block[set][way].data;
                cout << dec << " lru: " << block[set][way].lru << endl; });

                break;
            }
        }
    }

    if (way == NUM_WAY)
    {
        cerr << "[" << NAME << "] " << __func__ << " no victim! set: " << set << endl;
        assert(0);
    }

    return way;
}

void CACHE::lru_update_notLLC(uint32_t set, uint32_t way)
{
    // update lru replacement state
    for (uint32_t i = 0; i < NUM_WAY; i++)
    {
        if (block[set][i].lru < block[set][way].lru)
        {
            block[set][i].lru++;
        }
    }
    block[set][way].lru = 0; // promote to the MRU position
}
void CACHE::lru_update(uint32_t set, uint32_t way, uint32_t cpu)
{
    if (cpu == 0)
    {
        NUM_WAY_t = 0;
        NUM_WAY_end = 15;
    }
    if (cpu == 1)
    {
        NUM_WAY_t = 15;
        NUM_WAY_end = NUM_WAY;
    }
    // update lru replacement state
    if (cpu == 0)
    {
        // cout<< "hii :"<<cpu <<endl;
        // cout<< block[set][way].lru <<endl;
    }
    for (uint32_t i = 0; i < NUM_WAY; i++)
    {

        // if(block[set][way].cpu==0 and cpu==0)
        //     cout<< block[set][i].lru <<" "<<block[set][i].cpu<<" "<<i<<endl;

        if (block[set][i].cpu == cpu and block[set][i].lru < block[set][way].lru)
        {
            block[set][i].lru++;
        }
    }
    block[set][way].lru = 0; // promote to the MRU position
}

void CACHE::replacement_final_stats()
{
}

#ifdef NO_CRC2_COMPILE
void InitReplacementState()
{
}

uint32_t GetVictimInSet(uint32_t cpu, uint32_t set, const BLOCK *current_set, uint64_t PC, uint64_t paddr, uint32_t type)
{
    return 0;
}

void UpdateReplacementState(uint32_t cpu, uint32_t set, uint32_t way, uint64_t paddr, uint64_t PC, uint64_t victim_addr, uint32_t type, uint8_t hit)
{
}

void PrintStats_Heartbeat()
{
}

void PrintStats()
{
}
#endif
