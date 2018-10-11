#pragma once

#include <bearshares/chain/evaluator.hpp>

#include <bearshares/private_message/private_message_operations.hpp>
#include <bearshares/private_message/private_message_plugin.hpp>

namespace bearshares { namespace private_message {

DEFINE_PLUGIN_EVALUATOR( private_message_plugin, bearshares::private_message::private_message_plugin_operation, private_message )

} }
