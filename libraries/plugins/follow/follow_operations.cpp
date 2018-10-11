#include <bearshares/follow/follow_operations.hpp>

#include <bearshares/protocol/operation_util_impl.hpp>

namespace bearshares { namespace follow {

void follow_operation::validate()const
{
   FC_ASSERT( follower != following, "You cannot follow yourself" );
}

void reblog_operation::validate()const
{
   FC_ASSERT( account != author, "You cannot reblog your own content" );
}

} } //bearshares::follow

DEFINE_OPERATION_TYPE( bearshares::follow::follow_plugin_operation )
