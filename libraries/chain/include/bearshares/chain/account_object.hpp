#pragma once
#include <fc/fixed_string.hpp>

#include <bearshares/protocol/authority.hpp>
#include <bearshares/protocol/bears_operations.hpp>

#include <bearshares/chain/bears_object_types.hpp>
#include <bearshares/chain/witness_objects.hpp>
#include <bearshares/chain/shared_authority.hpp>

#include <boost/multi_index/composite_key.hpp>

#include <numeric>

namespace bearshares { namespace chain {

   using bearshares::protocol::authority;

   class account_object : public object< account_object_type, account_object >
   {
      account_object() = delete;

      public:
         template<typename Constructor, typename Allocator>
         account_object( Constructor&& c, allocator< Allocator > a )
            :json_metadata( a )
         {
            c(*this);
         };

         id_type           id;

         account_name_type name;
         public_key_type   memo_key;
         shared_string     json_metadata;
         account_name_type proxy;

         time_point_sec    last_account_update;

         time_point_sec    created;
         bool              mined = true;
         bool              owner_challenged = false;
         bool              active_challenged = false;
         time_point_sec    last_owner_proved = time_point_sec::min();
         time_point_sec    last_active_proved = time_point_sec::min();
         account_name_type recovery_account;
         account_name_type reset_account = BEARSHARES_NULL_ACCOUNT;
         time_point_sec    last_account_recovery;
         uint32_t          comment_count = 0;
         uint32_t          lifetime_vote_count = 0;
         uint32_t          post_count = 0;

         bool              can_vote = true;
         uint16_t          voting_power = BEARSHARES_100_PERCENT;   ///< current voting power of this account, it falls after every vote
         time_point_sec    last_vote_time; ///< used to increase the voting power of this account the longer it goes without voting.

         asset             balance = asset( 0, BEARS_SYMBOL );  ///< total liquid shares held by this account
         asset             savings_balance = asset( 0, BEARS_SYMBOL );  ///< total liquid shares held by this account

         /**
          *  BSD Deposits pay interest based upon the interest rate set by witnesses. The purpose of these
          *  fields is to track the total (time * bsd_balance) that it is held. Then at the appointed time
          *  interest can be paid using the following equation:
          *
          *  interest = interest_rate * bsd_seconds / seconds_per_year
          *
          *  Every time the bsd_balance is updated the bsd_seconds is also updated. If at least
          *  BEARSHARES_MIN_COMPOUNDING_INTERVAL_SECONDS has past since bsd_last_interest_payment then
          *  interest is added to bsd_balance.
          *
          *  @defgroup bsd_data bsd Balance Data
          */
         ///@{
         asset             bsd_balance = asset( 0, BSD_SYMBOL ); /// total bsd balance
         uint128_t         bsd_seconds; ///< total bsd * how long it has been hel
         time_point_sec    bsd_seconds_last_update; ///< the last time the bsd_seconds was updated
         time_point_sec    bsd_last_interest_payment; ///< used to pay interest at most once per month


         asset             savings_bsd_balance = asset( 0, BSD_SYMBOL ); /// total bsd balance
         uint128_t         savings_bsd_seconds; ///< total bsd * how long it has been hel
         time_point_sec    savings_bsd_seconds_last_update; ///< the last time the bsd_seconds was updated
         time_point_sec    savings_bsd_last_interest_payment; ///< used to pay interest at most once per month

         uint8_t           savings_withdraw_requests = 0;
         ///@}

         asset             reward_bsd_balance = asset( 0, BSD_SYMBOL );
         asset             reward_bears_balance = asset( 0, BEARS_SYMBOL );
         asset             reward_coining_balance = asset( 0, COINS_SYMBOL );
         asset             reward_coining_bears = asset( 0, BEARS_SYMBOL );

         share_type        curation_rewards = 0;
         share_type        posting_rewards = 0;

         asset             coining_shares = asset( 0, COINS_SYMBOL ); ///< total coining shares held by this account, controls its voting power
         asset             delegated_coining_shares = asset( 0, COINS_SYMBOL );
         asset             received_coining_shares = asset( 0, COINS_SYMBOL );

         asset             coining_withdraw_rate = asset( 0, COINS_SYMBOL ); ///< at the time this is updated it can be at most coining_shares/104
         time_point_sec    next_coining_withdrawal = fc::time_point_sec::maximum(); ///< after every withdrawal this is incremented by 1 week
         share_type        withdrawn = 0; /// Track how many shares have been withdrawn
         share_type        to_withdraw = 0; /// Might be able to look this up with operation history.
         uint16_t          withdraw_routes = 0;

         fc::array<share_type, BEARSHARES_MAX_PROXY_RECURSION_DEPTH> proxied_vsf_votes;// = std::vector<share_type>( BEARSHARES_MAX_PROXY_RECURSION_DEPTH, 0 ); ///< the total VFS votes proxied to this account

         uint16_t          witnesses_voted_for = 0;

         time_point_sec    last_post;
         time_point_sec    last_root_post = fc::time_point_sec::min();
         uint32_t          post_bandwidth = 0;

         /// This function should be used only when the account votes for a witness directly
         share_type        witness_vote_weight()const {
            return std::accumulate( proxied_vsf_votes.begin(),
                                    proxied_vsf_votes.end(),
                                    coining_shares.amount );
         }
         share_type        proxied_vsf_votes_total()const {
            return std::accumulate( proxied_vsf_votes.begin(),
                                    proxied_vsf_votes.end(),
                                    share_type() );
         }

         asset effective_coining_shares()const { return coining_shares - delegated_coining_shares + received_coining_shares; }
   };

   class account_authority_object : public object< account_authority_object_type, account_authority_object >
   {
      account_authority_object() = delete;

      public:
         template< typename Constructor, typename Allocator >
         account_authority_object( Constructor&& c, allocator< Allocator > a )
            : owner( a ), active( a ), posting( a )
         {
            c( *this );
         }

         id_type           id;

         account_name_type account;

         shared_authority  owner;   ///< used for backup control, can set owner or active
         shared_authority  active;  ///< used for all monetary operations, can set active or posting
         shared_authority  posting; ///< used for voting and posting

         time_point_sec    last_owner_update;
   };

   class coining_delegation_object : public object< coining_delegation_object_type, coining_delegation_object >
   {
      public:
         template< typename Constructor, typename Allocator >
         coining_delegation_object( Constructor&& c, allocator< Allocator > a )
         {
            c( *this );
         }

         coining_delegation_object() {}

         id_type           id;
         account_name_type delegator;
         account_name_type delegatee;
         asset             coining_shares;
         time_point_sec    min_delegation_time;
   };

   class coining_delegation_expiration_object : public object< coining_delegation_expiration_object_type, coining_delegation_expiration_object >
   {
      public:
         template< typename Constructor, typename Allocator >
         coining_delegation_expiration_object( Constructor&& c, allocator< Allocator > a )
         {
            c( *this );
         }

         coining_delegation_expiration_object() {}

         id_type           id;
         account_name_type delegator;
         asset             coining_shares;
         time_point_sec    expiration;
   };

   class owner_authority_history_object : public object< owner_authority_history_object_type, owner_authority_history_object >
   {
      owner_authority_history_object() = delete;

      public:
         template< typename Constructor, typename Allocator >
         owner_authority_history_object( Constructor&& c, allocator< Allocator > a )
            :previous_owner_authority( shared_authority::allocator_type( a.get_segment_manager() ) )
         {
            c( *this );
         }

         id_type           id;

         account_name_type account;
         shared_authority  previous_owner_authority;
         time_point_sec    last_valid_time;
   };

   class account_recovery_request_object : public object< account_recovery_request_object_type, account_recovery_request_object >
   {
      account_recovery_request_object() = delete;

      public:
         template< typename Constructor, typename Allocator >
         account_recovery_request_object( Constructor&& c, allocator< Allocator > a )
            :new_owner_authority( shared_authority::allocator_type( a.get_segment_manager() ) )
         {
            c( *this );
         }

         id_type           id;

         account_name_type account_to_recover;
         shared_authority  new_owner_authority;
         time_point_sec    expires;
   };

   class change_recovery_account_request_object : public object< change_recovery_account_request_object_type, change_recovery_account_request_object >
   {
      public:
         template< typename Constructor, typename Allocator >
         change_recovery_account_request_object( Constructor&& c, allocator< Allocator > a )
         {
            c( *this );
         }

         id_type           id;

         account_name_type account_to_recover;
         account_name_type recovery_account;
         time_point_sec    effective_on;
   };

   struct by_name;
   struct by_proxy;
   struct by_last_post;
   struct by_next_coining_withdrawal;
   struct by_bears_balance;
   struct by_smp_balance;
   struct by_smd_balance;
   struct by_post_count;
   struct by_vote_count;

   /**
    * @ingroup object_index
    */
   typedef multi_index_container<
      account_object,
      indexed_by<
         ordered_unique< tag< by_id >,
            member< account_object, account_id_type, &account_object::id > >,
         ordered_unique< tag< by_name >,
            member< account_object, account_name_type, &account_object::name > >,
         ordered_unique< tag< by_proxy >,
            composite_key< account_object,
               member< account_object, account_name_type, &account_object::proxy >,
               member< account_object, account_id_type, &account_object::id >
            > /// composite key by proxy
         >,
         ordered_unique< tag< by_next_coining_withdrawal >,
            composite_key< account_object,
               member< account_object, time_point_sec, &account_object::next_coining_withdrawal >,
               member< account_object, account_id_type, &account_object::id >
            > /// composite key by_next_coining_withdrawal
         >,
         ordered_unique< tag< by_last_post >,
            composite_key< account_object,
               member< account_object, time_point_sec, &account_object::last_post >,
               member< account_object, account_id_type, &account_object::id >
            >,
            composite_key_compare< std::greater< time_point_sec >, std::less< account_id_type > >
         >,
         ordered_unique< tag< by_bears_balance >,
            composite_key< account_object,
               member< account_object, asset, &account_object::balance >,
               member< account_object, account_id_type, &account_object::id >
            >,
            composite_key_compare< std::greater< asset >, std::less< account_id_type > >
         >,
         ordered_unique< tag< by_smp_balance >,
            composite_key< account_object,
               member< account_object, asset, &account_object::coining_shares >,
               member< account_object, account_id_type, &account_object::id >
            >,
            composite_key_compare< std::greater< asset >, std::less< account_id_type > >
         >,
         ordered_unique< tag< by_smd_balance >,
            composite_key< account_object,
               member< account_object, asset, &account_object::bsd_balance >,
               member< account_object, account_id_type, &account_object::id >
            >,
            composite_key_compare< std::greater< asset >, std::less< account_id_type > >
         >,
         ordered_unique< tag< by_post_count >,
            composite_key< account_object,
               member< account_object, uint32_t, &account_object::post_count >,
               member< account_object, account_id_type, &account_object::id >
            >,
            composite_key_compare< std::greater< uint32_t >, std::less< account_id_type > >
         >,
         ordered_unique< tag< by_vote_count >,
            composite_key< account_object,
               member< account_object, uint32_t, &account_object::lifetime_vote_count >,
               member< account_object, account_id_type, &account_object::id >
            >,
            composite_key_compare< std::greater< uint32_t >, std::less< account_id_type > >
         >
      >,
      allocator< account_object >
   > account_index;

   struct by_account;
   struct by_last_valid;

   typedef multi_index_container <
      owner_authority_history_object,
      indexed_by <
         ordered_unique< tag< by_id >,
            member< owner_authority_history_object, owner_authority_history_id_type, &owner_authority_history_object::id > >,
         ordered_unique< tag< by_account >,
            composite_key< owner_authority_history_object,
               member< owner_authority_history_object, account_name_type, &owner_authority_history_object::account >,
               member< owner_authority_history_object, time_point_sec, &owner_authority_history_object::last_valid_time >,
               member< owner_authority_history_object, owner_authority_history_id_type, &owner_authority_history_object::id >
            >,
            composite_key_compare< std::less< account_name_type >, std::less< time_point_sec >, std::less< owner_authority_history_id_type > >
         >
      >,
      allocator< owner_authority_history_object >
   > owner_authority_history_index;

   struct by_last_owner_update;

   typedef multi_index_container <
      account_authority_object,
      indexed_by <
         ordered_unique< tag< by_id >,
            member< account_authority_object, account_authority_id_type, &account_authority_object::id > >,
         ordered_unique< tag< by_account >,
            composite_key< account_authority_object,
               member< account_authority_object, account_name_type, &account_authority_object::account >,
               member< account_authority_object, account_authority_id_type, &account_authority_object::id >
            >,
            composite_key_compare< std::less< account_name_type >, std::less< account_authority_id_type > >
         >,
         ordered_unique< tag< by_last_owner_update >,
            composite_key< account_authority_object,
               member< account_authority_object, time_point_sec, &account_authority_object::last_owner_update >,
               member< account_authority_object, account_authority_id_type, &account_authority_object::id >
            >,
            composite_key_compare< std::greater< time_point_sec >, std::less< account_authority_id_type > >
         >
      >,
      allocator< account_authority_object >
   > account_authority_index;

   struct by_delegation;

   typedef multi_index_container <
      coining_delegation_object,
      indexed_by <
         ordered_unique< tag< by_id >,
            member< coining_delegation_object, coining_delegation_id_type, &coining_delegation_object::id > >,
         ordered_unique< tag< by_delegation >,
            composite_key< coining_delegation_object,
               member< coining_delegation_object, account_name_type, &coining_delegation_object::delegator >,
               member< coining_delegation_object, account_name_type, &coining_delegation_object::delegatee >
            >,
            composite_key_compare< std::less< account_name_type >, std::less< account_name_type > >
         >
      >,
      allocator< coining_delegation_object >
   > coining_delegation_index;

   struct by_expiration;
   struct by_account_expiration;

   typedef multi_index_container <
      coining_delegation_expiration_object,
      indexed_by <
         ordered_unique< tag< by_id >,
            member< coining_delegation_expiration_object, coining_delegation_expiration_id_type, &coining_delegation_expiration_object::id > >,
         ordered_unique< tag< by_expiration >,
            composite_key< coining_delegation_expiration_object,
               member< coining_delegation_expiration_object, time_point_sec, &coining_delegation_expiration_object::expiration >,
               member< coining_delegation_expiration_object, coining_delegation_expiration_id_type, &coining_delegation_expiration_object::id >
            >,
            composite_key_compare< std::less< time_point_sec >, std::less< coining_delegation_expiration_id_type > >
         >,
         ordered_unique< tag< by_account_expiration >,
            composite_key< coining_delegation_expiration_object,
               member< coining_delegation_expiration_object, account_name_type, &coining_delegation_expiration_object::delegator >,
               member< coining_delegation_expiration_object, time_point_sec, &coining_delegation_expiration_object::expiration >,
               member< coining_delegation_expiration_object, coining_delegation_expiration_id_type, &coining_delegation_expiration_object::id >
            >,
            composite_key_compare< std::less< account_name_type >, std::less< time_point_sec >, std::less< coining_delegation_expiration_id_type > >
         >
      >,
      allocator< coining_delegation_expiration_object >
   > coining_delegation_expiration_index;

   struct by_expiration;

   typedef multi_index_container <
      account_recovery_request_object,
      indexed_by <
         ordered_unique< tag< by_id >,
            member< account_recovery_request_object, account_recovery_request_id_type, &account_recovery_request_object::id > >,
         ordered_unique< tag< by_account >,
            composite_key< account_recovery_request_object,
               member< account_recovery_request_object, account_name_type, &account_recovery_request_object::account_to_recover >,
               member< account_recovery_request_object, account_recovery_request_id_type, &account_recovery_request_object::id >
            >,
            composite_key_compare< std::less< account_name_type >, std::less< account_recovery_request_id_type > >
         >,
         ordered_unique< tag< by_expiration >,
            composite_key< account_recovery_request_object,
               member< account_recovery_request_object, time_point_sec, &account_recovery_request_object::expires >,
               member< account_recovery_request_object, account_recovery_request_id_type, &account_recovery_request_object::id >
            >,
            composite_key_compare< std::less< time_point_sec >, std::less< account_recovery_request_id_type > >
         >
      >,
      allocator< account_recovery_request_object >
   > account_recovery_request_index;

   struct by_effective_date;

   typedef multi_index_container <
      change_recovery_account_request_object,
      indexed_by <
         ordered_unique< tag< by_id >,
            member< change_recovery_account_request_object, change_recovery_account_request_id_type, &change_recovery_account_request_object::id > >,
         ordered_unique< tag< by_account >,
            composite_key< change_recovery_account_request_object,
               member< change_recovery_account_request_object, account_name_type, &change_recovery_account_request_object::account_to_recover >,
               member< change_recovery_account_request_object, change_recovery_account_request_id_type, &change_recovery_account_request_object::id >
            >,
            composite_key_compare< std::less< account_name_type >, std::less< change_recovery_account_request_id_type > >
         >,
         ordered_unique< tag< by_effective_date >,
            composite_key< change_recovery_account_request_object,
               member< change_recovery_account_request_object, time_point_sec, &change_recovery_account_request_object::effective_on >,
               member< change_recovery_account_request_object, change_recovery_account_request_id_type, &change_recovery_account_request_object::id >
            >,
            composite_key_compare< std::less< time_point_sec >, std::less< change_recovery_account_request_id_type > >
         >
      >,
      allocator< change_recovery_account_request_object >
   > change_recovery_account_request_index;
} }

FC_REFLECT( bearshares::chain::account_object,
             (id)(name)(memo_key)(json_metadata)(proxy)(last_account_update)
             (created)(mined)
             (owner_challenged)(active_challenged)(last_owner_proved)(last_active_proved)(recovery_account)(last_account_recovery)(reset_account)
             (comment_count)(lifetime_vote_count)(post_count)(can_vote)(voting_power)(last_vote_time)
             (balance)
             (savings_balance)
             (bsd_balance)(bsd_seconds)(bsd_seconds_last_update)(bsd_last_interest_payment)
             (savings_bsd_balance)(savings_bsd_seconds)(savings_bsd_seconds_last_update)(savings_bsd_last_interest_payment)(savings_withdraw_requests)
             (reward_bears_balance)(reward_bsd_balance)(reward_coining_balance)(reward_coining_bears)
             (coining_shares)(delegated_coining_shares)(received_coining_shares)
             (coining_withdraw_rate)(next_coining_withdrawal)(withdrawn)(to_withdraw)(withdraw_routes)
             (curation_rewards)
             (posting_rewards)
             (proxied_vsf_votes)(witnesses_voted_for)
             (last_post)(last_root_post)(post_bandwidth)
          )
CHAINBASE_SET_INDEX_TYPE( bearshares::chain::account_object, bearshares::chain::account_index )

FC_REFLECT( bearshares::chain::account_authority_object,
             (id)(account)(owner)(active)(posting)(last_owner_update)
)
CHAINBASE_SET_INDEX_TYPE( bearshares::chain::account_authority_object, bearshares::chain::account_authority_index )

FC_REFLECT( bearshares::chain::coining_delegation_object,
            (id)(delegator)(delegatee)(coining_shares)(min_delegation_time) )
CHAINBASE_SET_INDEX_TYPE( bearshares::chain::coining_delegation_object, bearshares::chain::coining_delegation_index )

FC_REFLECT( bearshares::chain::coining_delegation_expiration_object,
            (id)(delegator)(coining_shares)(expiration) )
CHAINBASE_SET_INDEX_TYPE( bearshares::chain::coining_delegation_expiration_object, bearshares::chain::coining_delegation_expiration_index )

FC_REFLECT( bearshares::chain::owner_authority_history_object,
             (id)(account)(previous_owner_authority)(last_valid_time)
          )
CHAINBASE_SET_INDEX_TYPE( bearshares::chain::owner_authority_history_object, bearshares::chain::owner_authority_history_index )

FC_REFLECT( bearshares::chain::account_recovery_request_object,
             (id)(account_to_recover)(new_owner_authority)(expires)
          )
CHAINBASE_SET_INDEX_TYPE( bearshares::chain::account_recovery_request_object, bearshares::chain::account_recovery_request_index )

FC_REFLECT( bearshares::chain::change_recovery_account_request_object,
             (id)(account_to_recover)(recovery_account)(effective_on)
          )
CHAINBASE_SET_INDEX_TYPE( bearshares::chain::change_recovery_account_request_object, bearshares::chain::change_recovery_account_request_index )
