#include "global.h"
#include "mem_alloc.h"
#include "stats.h"
#include "dl_detect.h"
#include "manager.h"
#include "query.h"
#include "plock.h"
#include "occ.h"
#include "vll.h"

mem_alloc mem_allocator;
Stats stats;
DL_detect dl_detector;
Manager * glob_manager;
Query_queue * query_queue;
Plock part_lock_man;
OptCC occ_man;
#if CC_ALG == VLL
VLLMan vll_man;
#endif 

bool volatile warmup_finish = false;
bool volatile enable_thread_mem_pool = false;
pthread_barrier_t warmup_bar;
#ifndef NOGRAPHITE
carbon_barrier_t enable_barrier;
#endif

ts_t g_abort_penalty = ABORT_PENALTY;
bool g_central_man = CENTRAL_MAN;
UInt32 g_ts_alloc = TS_ALLOC;
bool g_key_order = KEY_ORDER;
bool g_no_dl = NO_DL;
ts_t g_timeout = TIMEOUT;
ts_t g_dl_loop_detect = DL_LOOP_DETECT;
bool g_ts_batch_alloc = TS_BATCH_ALLOC;
UInt32 g_ts_batch_num = TS_BATCH_NUM;

bool g_part_alloc = PART_ALLOC;
bool g_mem_pad = MEM_PAD;
UInt32 g_cc_alg = CC_ALG;
ts_t g_query_intvl = QUERY_INTVL;
UInt32 g_part_per_txn = PART_PER_TXN;
double g_perc_multi_part = PERC_MULTI_PART;
double g_read_perc = READ_PERC;
double g_write_perc = WRITE_PERC;
double g_zipf_theta = ZIPF_THETA;
bool g_prt_lat_distr = PRT_LAT_DISTR;
UInt32 g_part_cnt = PART_CNT;
UInt32 g_virtual_part_cnt = VIRTUAL_PART_CNT;
UInt32 g_thread_cnt = THREAD_CNT;
UInt64 g_synth_table_size = SYNTH_TABLE_SIZE;
UInt32 g_req_per_query = REQ_PER_QUERY;
UInt32 g_field_per_tuple = FIELD_PER_TUPLE;
UInt32 g_init_parallelism = INIT_PARALLELISM;
double g_last_retire = BB_LAST_RETIRE;
double g_specified_ratio = SPECIFIED_RATIO;
double g_flip_ratio = FLIP_RATIO;
double g_long_txn_ratio = LONG_TXN_RATIO;
double g_long_txn_read_ratio = LONG_TXN_READ_RATIO;

UInt32 g_num_wh = NUM_WH;
double g_perc_payment = PERC_PAYMENT;
double g_perc_delivery = PERC_DELIVERY;
double g_perc_orderstatus = PERC_ORDERSTATUS;
double g_perc_stocklevel = PERC_STOCKLEVEL;
double g_perc_neworder = 1 - (g_perc_payment + g_perc_delivery + g_perc_orderstatus + g_perc_stocklevel);
bool g_wh_update = WH_UPDATE;
//char * output_file = NULL;


#if CC_ALG == WOUND_WAIT
string cc_name = "WOUND_WAIT";
#elif CC_ALG == NO_WAIT
string cc_name = "NO_WAIT";
#elif CC_ALG == WAIT_DIE
string cc_name = "WAIT_DIE";
#elif CC_ALG == BAMBOO
string cc_name = "BAMBOO";
#elif CC_ALG == SILO
string cc_name = "SILO";
#elif CC_ALG == TICTOC
string cc_name = "TICTOC";
#elif CC_ALG == HEKATON
string cc_name = "HEKATON";
#elif CC_ALG == SLER
string cc_name = "SLER";
#endif


#if TEST_NUM == 1
string test_num = "1";
#elif TEST_NUM == 2
string test_num = "2";
#elif TEST_NUM == 3
string test_num = "3";
#elif TEST_NUM == 4
string test_num = "4";
#endif

#if TEST_INDEX == 1
string test_index = "1";
#elif TEST_INDEX == 2
string test_index = "2";
#elif TEST_INDEX == 3
string test_index = "3";
#elif TEST_INDEX == 4
string test_index = "4";
#elif TEST_INDEX == 5
string test_index = "5";
#endif

//string temp ="/home/xyw/SLER/Bamboo-Public-dbx1000-bamboo/results_background/test_"+ test_num + "_" + cc_name +".txt";
//string temp ="/home/xyw/SLER/Bamboo-Public-dbx1000-bamboo/results_synthetic_ycsb/test_"+ test_num + "_" + cc_name +".txt";
//string temp ="/home/xyw/SLER/Bamboo-Public-dbx1000-bamboo/results_YCSB/test_"+ test_num + "_" + cc_name +".txt";
//string temp ="/home/xyw/SLER/Bamboo-Public-dbx1000-bamboo/results_TPCC/test_"+ test_num + "_" + cc_name +".txt";

//string temp ="/home/xyw/SLER/Bamboo-Public-dbx1000-bamboo/results_YCSB/test_" + test_index + "/" + "test_"+ test_num + "_" + cc_name + ".txt";
string temp ="/home/xyw/SLER/Bamboo-Public-dbx1000-bamboo/results_synthetic_ycsb/test_" + test_index + "/" + "test_"+ test_num + "_" + cc_name + ".txt";
//string temp ="/home/xyw/SLER/Bamboo-Public-dbx1000-bamboo/results_TPCC/test_" + test_index + "/" + "test_"+ test_num + "_" + cc_name + ".txt";
//

char * output_file = const_cast<char *>(temp.c_str());

map<string, string> g_params;

#if TPCC_SMALL
UInt32 g_max_items = 10000;
UInt32 g_cust_per_dist = 2000;
#else 
UInt32 g_max_items = 100000;
UInt32 g_cust_per_dist = 3000;
#endif
