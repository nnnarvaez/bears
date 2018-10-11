#pragma once

#include <bearshares/account_statistics/account_statistics_plugin.hpp>

#include <fc/api.hpp>

namespace bearshares{ namespace app {
   struct api_context;
} }

namespace bearshares { namespace account_statistics {

namespace detail
{
   class account_statistics_api_impl;
}

class account_statistics_api
{
   public:
      account_statistics_api( const bearshares::app::api_context& ctx );

      void on_api_startup();

   private:
      std::shared_ptr< detail::account_statistics_api_impl > _my;
};

} } // bearshares::account_statistics

FC_API( bearshares::account_statistics::account_statistics_api, )