#pragma once

#include <bearshares/protocol/asset.hpp>

namespace bearshares { namespace chain { namespace util {

using bearshares::protocol::asset;
using bearshares::protocol::price;

inline asset to_bsd( const price& p, const asset& bears )
{
   FC_ASSERT( bears.symbol == BEARS_SYMBOL );
   if( p.is_null() )
      return asset( 0, BSD_SYMBOL );
   return bears * p;
}

inline asset to_bears( const price& p, const asset& bsd )
{
   FC_ASSERT( bsd.symbol == BSD_SYMBOL );
   if( p.is_null() )
      return asset( 0, BEARS_SYMBOL );
   return bsd * p;
}

} } }
