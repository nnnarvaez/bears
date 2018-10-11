/*
 * Copyright (c) 2016 Bearshares, Inc., and contributors.
 */
#pragma once

#define BEARSHARES_BLOCKCHAIN_VERSION              ( version(0, 19, 6) )
#define BEARSHARES_BLOCKCHAIN_HARDFORK_VERSION     ( hardfork_version( BEARSHARES_BLOCKCHAIN_VERSION ) )

#ifdef IS_TEST_NET
#define BEARSHARES_INIT_PRIVATE_KEY                (fc::ecc::private_key::regenerate(fc::sha256::hash(std::string("init_key"))))
#define BEARSHARES_INIT_PUBLIC_KEY_STR             (std::string( bearshares::protocol::public_key_type(BEARSHARES_INIT_PRIVATE_KEY.get_public_key()) ))
#define BEARSHARES_CHAIN_ID                        (fc::sha256::hash("testnet"))

#define COINS_SYMBOL  (uint64_t(6) | (uint64_t('C') << 8) | (uint64_t('O') << 16) | (uint64_t('I') << 24) | (uint64_t('N') << 32) | (uint64_t('S') << 40)) ///< COINS with 6 digits of precision
#define BEARS_SYMBOL  (uint64_t(3) | (uint64_t('T') << 8) | (uint64_t('E') << 16) | (uint64_t('S') << 24) | (uint64_t('T') << 32) | (uint64_t('S') << 40)) ///< BEARS with 3 digits of precision
#define BSD_SYMBOL    (uint64_t(3) | (uint64_t('T') << 8) | (uint64_t('B') << 16) | (uint64_t('D') << 24) ) ///< Test Backed Dollars with 3 digits of precision
#define SHRD_SYMBOL   (uint64_t(3) | (uint64_t('T') << 8) | (uint64_t('S') << 16) | (uint64_t('T') << 24) | (uint64_t('D') << 32) ) ///< Test Dollars with 3 digits of precision

#define BEARSHARES_SYMBOL                          "TEST"
#define BEARSHARES_ADDRESS_PREFIX                  "TST"

#define BEARSHARES_GENESIS_TIME                    (fc::time_point_sec(1451606400))
#define BEARSHARES_MINING_TIME                     (fc::time_point_sec(1451606400))
#define BEARSHARES_CASHOUT_WINDOW_SECONDS          (60*60) /// 1 hr
#define BEARSHARES_CASHOUT_WINDOW_SECONDS_PRE_HF12 (BEARSHARES_CASHOUT_WINDOW_SECONDS)
#define BEARSHARES_CASHOUT_WINDOW_SECONDS_PRE_HF17 (BEARSHARES_CASHOUT_WINDOW_SECONDS)
#define BEARSHARES_SECOND_CASHOUT_WINDOW           (60*60*24*3) /// 3 days
#define BEARSHARES_MAX_CASHOUT_WINDOW_SECONDS      (60*60*24) /// 1 day
#define BEARSHARES_VOTE_CHANGE_LOCKOUT_PERIOD      (60*10) /// 10 minutes
#define BEARSHARES_UPVOTE_LOCKOUT_HF7              (fc::minutes(1))
#define BEARSHARES_UPVOTE_LOCKOUT_HF17             (fc::minutes(5))


#define BEARSHARES_ORIGINAL_MIN_ACCOUNT_CREATION_FEE 0
#define BEARSHARES_MIN_ACCOUNT_CREATION_FEE          0

#define BEARSHARES_OWNER_AUTH_RECOVERY_PERIOD                  fc::seconds(60)
#define BEARSHARES_ACCOUNT_RECOVERY_REQUEST_EXPIRATION_PERIOD  fc::seconds(12)
#define BEARSHARES_OWNER_UPDATE_LIMIT                          fc::seconds(0)
#define BEARSHARES_OWNER_AUTH_HISTORY_TRACKING_START_BLOCK_NUM 1
#else // IS LIVE BEARS NETWORK

#define BEARSHARES_INIT_PUBLIC_KEY_STR             "SHR7YDq7bh9EG3oufCAPRjf1ZESqCqjdjj55Xp2QXDTnYndVqxBom"
#define BEARSHARES_CHAIN_ID                        (fc::sha256::hash("I love Pakistan"))//(bearshares::protocol::chain_id_type())
#define COINS_SYMBOL  (uint64_t(6) | (uint64_t('C') << 8) | (uint64_t('O') << 16) | (uint64_t('I') << 24) | (uint64_t('N') << 32) | (uint64_t('S') << 40)) ///< COINS with 6 digits of precision
#define BEARS_SYMBOL  (uint64_t(3) | (uint64_t('B') << 8) | (uint64_t('E') << 16) | (uint64_t('A') << 24) | (uint64_t('R') << 32) | (uint64_t('S') << 40)) ///< BEARS with 3 digits of precision
#define BSD_SYMBOL    (uint64_t(3) | (uint64_t('B') << 8) | (uint64_t('S') << 16) | (uint64_t('D') << 24) ) ///< BEARS Backed Dollars with 3 digits of precision
#define SHRD_SYMBOL   (uint64_t(3) | (uint64_t('S') << 8) | (uint64_t('H') << 16) | (uint64_t('R') << 24) | (uint64_t('D') << 32) ) ///< BEARS Dollars with 3 digits of precision
#define BEARSHARES_SYMBOL                          "BEARS"
#define BEARSHARES_ADDRESS_PREFIX                  "SHR"

#define BEARSHARES_GENESIS_TIME                    (fc::time_point_sec(1458835200))
#define BEARSHARES_MINING_TIME                     (fc::time_point_sec(1458838800))
#define BEARSHARES_CASHOUT_WINDOW_SECONDS_PRE_HF12 (60*60*24)    /// 1 day
#define BEARSHARES_CASHOUT_WINDOW_SECONDS_PRE_HF17 (60*60*12)    /// 12 hours
#define BEARSHARES_CASHOUT_WINDOW_SECONDS          (60*60*24*7)  /// 7 days
#define BEARSHARES_SECOND_CASHOUT_WINDOW           (60*60*24*30) /// 30 days
#define BEARSHARES_MAX_CASHOUT_WINDOW_SECONDS      (60*60*24*14) /// 2 weeks
#define BEARSHARES_VOTE_CHANGE_LOCKOUT_PERIOD      (60*60*2)     /// 2 hours
#define BEARSHARES_UPVOTE_LOCKOUT_HF7              (fc::minutes(1))
#define BEARSHARES_UPVOTE_LOCKOUT_HF17             (fc::hours(12))

#define BEARSHARES_ORIGINAL_MIN_ACCOUNT_CREATION_FEE  100000
#define BEARSHARES_MIN_ACCOUNT_CREATION_FEE           1

#define BEARSHARES_OWNER_AUTH_RECOVERY_PERIOD                  fc::days(30)
#define BEARSHARES_ACCOUNT_RECOVERY_REQUEST_EXPIRATION_PERIOD  fc::days(1)
#define BEARSHARES_OWNER_UPDATE_LIMIT                          fc::minutes(60)
#define BEARSHARES_OWNER_AUTH_HISTORY_TRACKING_START_BLOCK_NUM 0

#endif

#define BEARSHARES_BLOCK_INTERVAL                  3
#define BEARSHARES_BLOCKS_PER_YEAR                 (365*24*60*60/BEARSHARES_BLOCK_INTERVAL)
#define BEARSHARES_BLOCKS_PER_DAY                  (24*60*60/BEARSHARES_BLOCK_INTERVAL)
#define BEARSHARES_START_COINING_BLOCK             (BEARSHARES_BLOCKS_PER_DAY * 7)
#define BEARSHARES_START_MINER_VOTING_BLOCK        (BEARSHARES_BLOCKS_PER_DAY * 30)

#define BEARSHARES_INIT_MINER_NAME                 "bearshare"
#define BEARSHARES_NUM_INIT_MINERS                 1
#define BEARSHARES_INIT_TIME                       (fc::time_point_sec());

#define BEARSHARES_MAX_WITNESSES                   21

#define BEARSHARES_MAX_VOTED_WITNESSES_HF0         19
#define BEARSHARES_MAX_MINER_WITNESSES_HF0         1
#define BEARSHARES_MAX_RUNNER_WITNESSES_HF0        1

#define BEARSHARES_MAX_VOTED_WITNESSES_HF17        20
#define BEARSHARES_MAX_MINER_WITNESSES_HF17        0
#define BEARSHARES_MAX_RUNNER_WITNESSES_HF17       1

#define BEARSHARES_HARDFORK_REQUIRED_WITNESSES     17 // 17 of the 21 dpos witnesses (20 elected and 1 virtual time) required for hardfork. This guarantees 75% participation on all subsequent rounds.
#define BEARSHARES_MAX_TIME_UNTIL_EXPIRATION       (60*60) // seconds,  aka: 1 hour
#define BEARSHARES_MAX_MEMO_SIZE                   2048
#define BEARSHARES_MAX_PROXY_RECURSION_DEPTH       4
#define BEARSHARES_COINING_WITHDRAW_INTERVALS_PRE_HF_16 104
#define BEARSHARES_COINING_WITHDRAW_INTERVALS      13
#define BEARSHARES_COINING_WITHDRAW_INTERVAL_SECONDS (60*60*24*7) /// 1 week per interval
#define BEARSHARES_MAX_WITHDRAW_ROUTES             10
#define BEARSHARES_SAVINGS_WITHDRAW_TIME        	(fc::days(3))
#define BEARSHARES_SAVINGS_WITHDRAW_REQUEST_LIMIT  100
#define BEARSHARES_VOTE_REGENERATION_SECONDS       (5*60*60*24) // 5 day
#define BEARSHARES_MAX_VOTE_CHANGES                5
#define BEARSHARES_REVERSE_AUCTION_WINDOW_SECONDS  (60*30) /// 30 minutes
#define BEARSHARES_MIN_VOTE_INTERVAL_SEC           3
#define BEARSHARES_VOTE_DUST_THRESHOLD             (50000000)

#define BEARSHARES_MIN_ROOT_COMMENT_INTERVAL       (fc::seconds(60*5)) // 5 minutes
#define BEARSHARES_MIN_REPLY_INTERVAL              (fc::seconds(20)) // 20 seconds
#define BEARSHARES_POST_AVERAGE_WINDOW             (60*60*24u) // 1 day
#define BEARSHARES_POST_MAX_BANDWIDTH              (4*BEARSHARES_100_PERCENT) // 2 posts per 1 days, average 1 every 12 hours
#define BEARSHARES_POST_WEIGHT_CONSTANT            (uint64_t(BEARSHARES_POST_MAX_BANDWIDTH) * BEARSHARES_POST_MAX_BANDWIDTH)

#define BEARSHARES_MAX_ACCOUNT_WITNESS_VOTES       30

#define BEARSHARES_100_PERCENT                     10000
#define BEARSHARES_1_PERCENT                       (BEARSHARES_100_PERCENT/100)
#define BEARSHARES_1_TENTH_PERCENT                 (BEARSHARES_100_PERCENT/1000)
#define BEARSHARES_DEFAULT_BSD_INTEREST_RATE       (10*BEARSHARES_1_PERCENT) ///< 10% APR

#define BEARSHARES_INFLATION_RATE_START_PERCENT    (978) // Fixes block 7,000,000 to 9.5%
#define BEARSHARES_INFLATION_RATE_STOP_PERCENT     (95) // 0.95%
#define BEARSHARES_INFLATION_NARROWING_PERIOD      (250000) // Narrow 0.01% every 250k blocks
#define BEARSHARES_CONTENT_REWARD_PERCENT          (75*BEARSHARES_1_PERCENT) //75% of inflation, 7.125% inflation
#define BEARSHARES_COINING_FUND_PERCENT            (15*BEARSHARES_1_PERCENT) //15% of inflation, 1.425% inflation

#define BEARSHARES_MINER_PAY_PERCENT               (BEARSHARES_1_PERCENT) // 1%
#define BEARSHARES_MIN_RATION                      100000
#define BEARSHARES_MAX_RATION_DECAY_RATE           (1000000)
#define BEARSHARES_FREE_TRANSACTIONS_WITH_NEW_ACCOUNT 100

#define BEARSHARES_BANDWIDTH_AVERAGE_WINDOW_SECONDS (60*60*24*7) ///< 1 week
#define BEARSHARES_BANDWIDTH_PRECISION             (uint64_t(1000000)) ///< 1 million
#define BEARSHARES_MAX_COMMENT_DEPTH_PRE_HF17      6
#define BEARSHARES_MAX_COMMENT_DEPTH               0xffff // 64k
#define BEARSHARES_SOFT_MAX_COMMENT_DEPTH          0xff // 255

#define BEARSHARES_MAX_RESERVE_RATIO               (20000)

#define BEARSHARES_CREATE_ACCOUNT_WITH_BEARS_MODIFIER 30
#define BEARSHARES_CREATE_ACCOUNT_DELEGATION_RATIO    5
#define BEARSHARES_CREATE_ACCOUNT_DELEGATION_TIME     fc::days(30)

#define BEARSHARES_MINING_REWARD                   asset( 1000, BEARS_SYMBOL )
#define BEARSHARES_EQUIHASH_N                      140
#define BEARSHARES_EQUIHASH_K                      6

#define BEARSHARES_LIQUIDITY_TIMEOUT_SEC           (fc::seconds(60*60*24*7)) // After one week volume is set to 0
#define BEARSHARES_MIN_LIQUIDITY_REWARD_PERIOD_SEC (fc::seconds(60)) // 1 minute required on books to receive volume
#define BEARSHARES_LIQUIDITY_REWARD_PERIOD_SEC     (60*60)
#define BEARSHARES_LIQUIDITY_REWARD_BLOCKS         (BEARSHARES_LIQUIDITY_REWARD_PERIOD_SEC/BEARSHARES_BLOCK_INTERVAL)
#define BEARSHARES_MIN_LIQUIDITY_REWARD            (asset( 1000*BEARSHARES_LIQUIDITY_REWARD_BLOCKS, BEARS_SYMBOL )) // Minumum reward to be paid out to liquidity providers
#define BEARSHARES_MIN_CONTENT_REWARD              BEARSHARES_MINING_REWARD
#define BEARSHARES_MIN_CURATE_REWARD               BEARSHARES_MINING_REWARD
#define BEARSHARES_MIN_PRODUCER_REWARD             BEARSHARES_MINING_REWARD
#define BEARSHARES_MIN_POW_REWARD                  BEARSHARES_MINING_REWARD

#define BEARSHARES_ACTIVE_CHALLENGE_FEE            asset( 2000, BEARS_SYMBOL )
#define BEARSHARES_OWNER_CHALLENGE_FEE             asset( 30000, BEARS_SYMBOL )
#define BEARSHARES_ACTIVE_CHALLENGE_COOLDOWN       fc::days(1)
#define BEARSHARES_OWNER_CHALLENGE_COOLDOWN        fc::days(1)

#define BEARSHARES_POST_REWARD_FUND_NAME           ("post")
#define BEARSHARES_COMMENT_REWARD_FUND_NAME        ("comment")
#define BEARSHARES_RECENT_RSHARES_DECAY_RATE_HF17  (fc::days(30))
#define BEARSHARES_RECENT_RSHARES_DECAY_RATE_HF19  (fc::days(15))
#define BEARSHARES_CONTENT_CONSTANT_HF0            (uint128_t(uint64_t(2000000000000ll)))
// note, if redefining these constants make sure calculate_claims doesn't overflow

// 5ccc e802 de5f
// int(expm1( log1p( 1 ) / BLOCKS_PER_YEAR ) * 2**BEARSHARES_APR_PERCENT_SHIFT_PER_BLOCK / 100000 + 0.5)
// we use 100000 here instead of 10000 because we end up creating an additional 9x for coining
#define BEARSHARES_APR_PERCENT_MULTIPLY_PER_BLOCK          ( (uint64_t( 0x5ccc ) << 0x20) \
                                                        | (uint64_t( 0xe802 ) << 0x10) \
                                                        | (uint64_t( 0xde5f )        ) \
                                                        )
// chosen to be the maximal value such that BEARSHARES_APR_PERCENT_MULTIPLY_PER_BLOCK * 2**64 * 100000 < 2**128
#define BEARSHARES_APR_PERCENT_SHIFT_PER_BLOCK             87

#define BEARSHARES_APR_PERCENT_MULTIPLY_PER_ROUND          ( (uint64_t( 0x79cc ) << 0x20 ) \
                                                        | (uint64_t( 0xf5c7 ) << 0x10 ) \
                                                        | (uint64_t( 0x3480 )         ) \
                                                        )

#define BEARSHARES_APR_PERCENT_SHIFT_PER_ROUND             83

// We have different constants for hourly rewards
// i.e. hex(int(math.expm1( math.log1p( 1 ) / HOURS_PER_YEAR ) * 2**BEARSHARES_APR_PERCENT_SHIFT_PER_HOUR / 100000 + 0.5))
#define BEARSHARES_APR_PERCENT_MULTIPLY_PER_HOUR           ( (uint64_t( 0x6cc1 ) << 0x20) \
                                                        | (uint64_t( 0x39a1 ) << 0x10) \
                                                        | (uint64_t( 0x5cbd )        ) \
                                                        )

// chosen to be the maximal value such that BEARSHARES_APR_PERCENT_MULTIPLY_PER_HOUR * 2**64 * 100000 < 2**128
#define BEARSHARES_APR_PERCENT_SHIFT_PER_HOUR              77

// These constants add up to GRAPHENE_100_PERCENT.  Each GRAPHENE_1_PERCENT is equivalent to 1% per year APY
// *including the corresponding 9x coining rewards*
#define BEARSHARES_CURATE_APR_PERCENT              3875
#define BEARSHARES_CONTENT_APR_PERCENT             3875
#define BEARSHARES_LIQUIDITY_APR_PERCENT            750
#define BEARSHARES_PRODUCER_APR_PERCENT             750
#define BEARSHARES_POW_APR_PERCENT                  750

#define BEARSHARES_MIN_PAYOUT_BSD                  (asset(20,BSD_SYMBOL))

#define BEARSHARES_BSD_STOP_PERCENT                (5*BEARSHARES_1_PERCENT ) // Stop printing BSD at 5% Market Cap
#define BEARSHARES_BSD_START_PERCENT               (2*BEARSHARES_1_PERCENT) // Start reducing printing of BSD at 2% Market Cap

#define BEARSHARES_MIN_ACCOUNT_NAME_LENGTH          3
#define BEARSHARES_MAX_ACCOUNT_NAME_LENGTH         16

#define BEARSHARES_MIN_PERMLINK_LENGTH             0
#define BEARSHARES_MAX_PERMLINK_LENGTH             256
#define BEARSHARES_MAX_WITNESS_URL_LENGTH          2048

#define BEARSHARES_INIT_SUPPLY                     int64_t(500000000000)
#define BEARSHARES_MAX_SHARE_SUPPLY                int64_t(1000000000000000ll)
#define BEARSHARES_MAX_SIG_CHECK_DEPTH             2

#define BEARSHARES_MIN_TRANSACTION_SIZE_LIMIT      1024
#define BEARSHARES_SECONDS_PER_YEAR                (uint64_t(60*60*24*365ll))

#define BEARSHARES_BSD_INTEREST_COMPOUND_INTERVAL_SEC  (60*60*24*30)
#define BEARSHARES_MAX_TRANSACTION_SIZE            (1024*64)
#define BEARSHARES_MIN_BLOCK_SIZE_LIMIT            (BEARSHARES_MAX_TRANSACTION_SIZE)
#define BEARSHARES_MAX_BLOCK_SIZE                  (BEARSHARES_MAX_TRANSACTION_SIZE*BEARSHARES_BLOCK_INTERVAL*2000)
#define BEARSHARES_MIN_BLOCK_SIZE                  115
#define BEARSHARES_BLOCKS_PER_HOUR                 (60*60/BEARSHARES_BLOCK_INTERVAL)
#define BEARSHARES_FEED_INTERVAL_BLOCKS            (10)//(BEARSHARES_BLOCKS_PER_HOUR)
#define BEARSHARES_FEED_HISTORY_WINDOW_PRE_HF_16   (24*7) /// 7 days * 24 hours per day
#define BEARSHARES_FEED_HISTORY_WINDOW             (12*7) // 3.5 days
#define BEARSHARES_MAX_FEED_AGE_SECONDS            (60)//(60*60*24*7) // 7 days
#define BEARSHARES_MIN_FEEDS                       (1)//(BEARSHARES_MAX_WITNESSES/3) /// protects the network from conversions before price has been established
#define BEARSHARES_CONVERSION_DELAY_PRE_HF_16      (fc::days(7))
#define BEARSHARES_CONVERSION_DELAY                (fc::hours(BEARSHARES_FEED_HISTORY_WINDOW)) //3.5 day conversion

#define BEARSHARES_MIN_UNDO_HISTORY                10
#define BEARSHARES_MAX_UNDO_HISTORY                10000

#define BEARSHARES_MIN_TRANSACTION_EXPIRATION_LIMIT (BEARSHARES_BLOCK_INTERVAL * 5) // 5 transactions per block
#define BEARSHARES_BLOCKCHAIN_PRECISION            uint64_t( 1000 )

#define BEARSHARES_BLOCKCHAIN_PRECISION_DIGITS     3
#define BEARSHARES_MAX_INSTANCE_ID                 (uint64_t(-1)>>16)
/** NOTE: making this a power of 2 (say 2^15) would greatly accelerate fee calcs */
#define BEARSHARES_MAX_AUTHORITY_MEMBERSHIP        10
#define BEARSHARES_MAX_ASSET_WHITELIST_AUTHORITIES 10
#define BEARSHARES_MAX_URL_LENGTH                  127

#define BEARSHARES_IRREVERSIBLE_THRESHOLD          (75 * BEARSHARES_1_PERCENT)

#define VIRTUAL_SCHEDULE_LAP_LENGTH  ( fc::uint128(uint64_t(-1)) )
#define VIRTUAL_SCHEDULE_LAP_LENGTH2 ( fc::uint128::max_value() )

/**
 *  Reserved Account IDs with special meaning
 */
///@{
/// Represents the current witnesses
#define BEARSHARES_MINER_ACCOUNT                   "miners"
/// Represents the canonical account with NO authority (nobody can access funds in null account)
#define BEARSHARES_NULL_ACCOUNT                    "null"
/// Represents the canonical account with WILDCARD authority (anybody can access funds in temp account)
#define BEARSHARES_TEMP_ACCOUNT                    "temp"
/// Represents the canonical account for specifying you will vote for directly (as opposed to a proxy)
#define BEARSHARES_PROXY_TO_SELF_ACCOUNT           ""
/// Represents the canonical root post parent account
#define BEARSHARES_ROOT_POST_PARENT                (account_name_type())
///@}
