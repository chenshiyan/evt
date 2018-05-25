/**
 *  @file
 *  @copyright defined in evt/LICENSE.txt
 */
#pragma once

#include <appbase/channel.hpp>
#include <appbase/method.hpp>

#include <evt/chain/block.hpp>
#include <evt/chain/block_state.hpp>
#include <evt/chain/trace.hpp>
#include <evt/chain/transaction_metadata.hpp>

namespace evt { namespace chain { namespace plugin_interface {
using namespace evt::chain;
using namespace appbase;

struct chain_plugin_interface;

namespace channels {
using accepted_block_header = channel_decl<struct accepted_block_header_tag, block_state_ptr>;
using accepted_block        = channel_decl<struct accepted_block_tag, block_state_ptr>;
using irreversible_block    = channel_decl<struct irreversible_block_tag, block_state_ptr>;
using accepted_transaction  = channel_decl<struct accepted_transaction_tag, transaction_metadata_ptr>;
using applied_transaction   = channel_decl<struct applied_transaction_tag, transaction_trace_ptr>;
using accepted_confirmation = channel_decl<struct accepted_confirmation_tag, header_confirmation>;

}  // namespace channels

namespace methods {
using get_block_by_number = method_decl<chain_plugin_interface, signed_block_ptr(uint32_t block_num)>;
using get_block_by_id     = method_decl<chain_plugin_interface, signed_block_ptr(const block_id_type& block_id)>;
using get_head_block_id   = method_decl<chain_plugin_interface, block_id_type()>;

using get_last_irreversible_block_number = method_decl<chain_plugin_interface, uint32_t()>;
}  // namespace methods

namespace incoming {
namespace channels {
using block       = channel_decl<struct block_tag, signed_block_ptr>;
using transaction = channel_decl<struct transaction_tag, packed_transaction_ptr>;
}  // namespace channels

namespace methods {
// synchronously push a block/trx to a single provider
using block_sync       = method_decl<chain_plugin_interface, void(const signed_block_ptr&), first_provider_policy>;
using transaction_sync = method_decl<chain_plugin_interface, transaction_trace_ptr(const packed_transaction_ptr&, bool), first_provider_policy>;
}  // namespace methods
}  // namespace incoming

namespace compat {
namespace channels {
using transaction_ack = channel_decl<struct accepted_transaction_tag, std::pair<fc::exception_ptr, packed_transaction_ptr>>;
}}  // namespace compat::channels

}}}  // namespace evt::chain::plugin_interface