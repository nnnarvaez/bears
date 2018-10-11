#pragma once
#include <bearshares/app/plugin.hpp>

#include <bearshares/chain/bears_object_types.hpp>

#include <boost/multi_index/composite_key.hpp>

//
// Plugins should #define their SPACE_ID's so plugins with
// conflicting SPACE_ID assignments can be compiled into the
// same binary (by simply re-assigning some of the conflicting #defined
// SPACE_ID's in a build script).
//
// Assignment of SPACE_ID's cannot be done at run-time because
// various template automagic depends on them being known at compile
// time.
//
#ifndef MARKET_HISTORY_SPACE_ID
#define MARKET_HISTORY_SPACE_ID 7
#endif

#ifndef MARKET_HISTORY_PLUGIN_NAME
#define MARKET_HISTORY_PLUGIN_NAME "market_history"
#endif


namespace bearshares { namespace market_history {

using namespace chain;
using bearshares::app::application;

enum market_history_object_types
{
   bucket_object_type        = ( MARKET_HISTORY_SPACE_ID << 8 ),
   order_history_object_type = ( MARKET_HISTORY_SPACE_ID << 8 ) + 1
};

namespace detail
{
   class market_history_plugin_impl;
}

class market_history_plugin : public bearshares::app::plugin
{
   public:
      market_history_plugin( application* app );
      virtual ~market_history_plugin();

      virtual std::string plugin_name()const override { return MARKET_HISTORY_PLUGIN_NAME; }
      virtual void plugin_set_program_options(
         boost::program_options::options_description& cli,
         boost::program_options::options_description& cfg ) override;
      virtual void plugin_initialize( const boost::program_options::variables_map& options ) override;
      virtual void plugin_startup() override;

      flat_set< uint32_t > get_tracked_buckets() const;
      uint32_t get_max_history_per_bucket() const;

   private:
      friend class detail::market_history_plugin_impl;
      std::unique_ptr< detail::market_history_plugin_impl > _my;
};

struct bucket_object : public object< bucket_object_type, bucket_object >
{
   template< typename Constructor, typename Allocator >
   bucket_object( Constructor&& c, allocator< Allocator > a )
   {
      c( *this );
   }

   id_type              id;

   fc::time_point_sec   open;
   uint32_t             seconds = 0;
   share_type           high_bears;
   share_type           high_bsd;
   share_type           low_bears;
   share_type           low_bsd;
   share_type           open_bears;
   share_type           open_bsd;
   share_type           close_bears;
   share_type           close_bsd;
   share_type           bears_volume;
   share_type           bsd_volume;

   price high()const { return asset( high_bsd, BSD_SYMBOL ) / asset( high_bears, BEARS_SYMBOL ); }
   price low()const { return asset( low_bsd, BSD_SYMBOL ) / asset( low_bears, BEARS_SYMBOL ); }
};

typedef oid< bucket_object > bucket_id_type;


struct order_history_object : public object< order_history_object_type, order_history_object >
{
   template< typename Constructor, typename Allocator >
   order_history_object( Constructor&& c, allocator< Allocator > a )
   {
      c( *this );
   }

   id_type                          id;

   fc::time_point_sec               time;
   protocol::fill_order_operation   op;
};

typedef oid< order_history_object > order_history_id_type;


struct by_bucket;
typedef multi_index_container<
   bucket_object,
   indexed_by<
      ordered_unique< tag< by_id >, member< bucket_object, bucket_id_type, &bucket_object::id > >,
      ordered_unique< tag< by_bucket >,
         composite_key< bucket_object,
            member< bucket_object, uint32_t, &bucket_object::seconds >,
            member< bucket_object, fc::time_point_sec, &bucket_object::open >
         >,
         composite_key_compare< std::less< uint32_t >, std::less< fc::time_point_sec > >
      >
   >,
   allocator< bucket_object >
> bucket_index;

struct by_time;
typedef multi_index_container<
   order_history_object,
   indexed_by<
      ordered_unique< tag< by_id >, member< order_history_object, order_history_id_type, &order_history_object::id > >,
      ordered_non_unique< tag< by_time >, member< order_history_object, time_point_sec, &order_history_object::time > >
   >,
   allocator< order_history_object >
> order_history_index;

} } // bearshares::market_history

FC_REFLECT( bearshares::market_history::bucket_object,
                     (id)
                     (open)(seconds)
                     (high_bears)(high_bsd)
                     (low_bears)(low_bsd)
                     (open_bears)(open_bsd)
                     (close_bears)(close_bsd)
                     (bears_volume)(bsd_volume) )
CHAINBASE_SET_INDEX_TYPE( bearshares::market_history::bucket_object, bearshares::market_history::bucket_index )

FC_REFLECT( bearshares::market_history::order_history_object,
                     (id)
                     (time)
                     (op) )
CHAINBASE_SET_INDEX_TYPE( bearshares::market_history::order_history_object, bearshares::market_history::order_history_index )
