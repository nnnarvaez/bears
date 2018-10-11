#pragma once
#include <bearshares/protocol/block_header.hpp>
#include <bearshares/protocol/transaction.hpp>

namespace bearshares { namespace protocol {

   struct signed_block : public signed_block_header
   {
      checksum_type calculate_merkle_root()const;
      vector<signed_transaction> transactions;
   };

} } // bearshares::protocol

FC_REFLECT_DERIVED( bearshares::protocol::signed_block, (bearshares::protocol::signed_block_header), (transactions) )
