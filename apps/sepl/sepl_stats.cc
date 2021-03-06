/* Copyright 2008 (C) Nicira, Inc. */
/* Copyright 2008 (C) Nicira, Inc.
 *
 * This file is part of NOX.
 *
 * NOX is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * NOX is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with NOX.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "sepl_stats.hh"
#include "vlog.hh"

using namespace vigil::applications;
using namespace vigil::container;

namespace vigil {
namespace applications {

static Vlog_module lg("sepl_stats");

Sepl_stats::Sepl_stats(const container::Context* c,
                       const xercesc::DOMNode*)
    : Component(c), n_allows(0), n_denies(0)
{ }

void
Sepl_stats::getInstance(const container::Context* ctxt,
                        Sepl_stats*& r)
{
    r = dynamic_cast<Sepl_stats*>
        (ctxt->get_by_interface(container::Interface_description
                                (typeid(Sepl_stats).name())));
}

void
Sepl_stats::set_record_rule_senders(uint32_t id, bool record)
{
    RuleStats::iterator rule = rules.find(id);
    if (rule == rules.end()) {
        if (record) {
            RuleStatsEntry newentry = { 0, true, eth_hash_set() };
            rules[id] = newentry;
        }
    } else {
        rule->second.record_senders = record;
        if (!record) {
            rule->second.sender_macs.clear();
        }
    }
}

void
Sepl_stats::record_stats(const ethernetaddr& sender,
                         const hash_set<uint32_t>& ids)
{
    for (hash_set<uint32_t>::const_iterator id = ids.begin();
         id != ids.end(); ++id)
    {
        RuleStats::iterator rule = rules.find(*id);
        if (rule == rules.end()) {
            RuleStatsEntry newentry = { 1, false, eth_hash_set() };
            rules[*id] = newentry;
        } else {
            ++(rule->second.count);
            if (rule->second.record_senders) {
                rule->second.sender_macs.insert(sender);
            }
        }
    }
}


void
Sepl_stats::get_rule_stats(uint32_t id, RuleStatsEntry& entry)
{
    RuleStats::iterator rule = rules.find(id);
    if (rule == rules.end()) {
        entry.count = 0;
        entry.record_senders = false;
        entry.sender_macs.clear();
    } else {
        entry = rule->second;
    }
}

void
Sepl_stats::remove_entry(uint32_t id)
{
    RuleStats::iterator rule = rules.find(id);
    if (rule != rules.end()) {
        rules.erase(rule);
        VLOG_DBG(lg, "Rule stats entry %u removed.", id);
    } else {
        VLOG_DBG(lg, "Rule stats entry %u not present to remove.", id);
    }
}

} // namespace applications
} // namespace vigil

REGISTER_COMPONENT(Simple_component_factory<Sepl_stats>,
                   Sepl_stats);

