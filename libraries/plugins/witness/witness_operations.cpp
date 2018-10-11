#include <bearshares/witness/witness_operations.hpp>

#include <bearshares/protocol/operation_util_impl.hpp>

namespace bearshares { namespace witness {

void enable_content_editing_operation::validate()const
{
   chain::validate_account_name( account );
}

} } // bearshares::witness

DEFINE_OPERATION_TYPE( bearshares::witness::witness_plugin_operation )
