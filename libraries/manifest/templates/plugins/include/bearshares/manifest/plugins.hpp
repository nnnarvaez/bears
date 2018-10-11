
#pragma once

#include <memory>
#include <string>
#include <vector>

namespace bearshares { namespace app {

class abstract_plugin;
class application;

} }

namespace bearshares { namespace plugin {

void initialize_plugin_factories();
std::shared_ptr< bearshares::app::abstract_plugin > create_plugin( const std::string& name, bearshares::app::application* app );
std::vector< std::string > get_available_plugins();

} }
