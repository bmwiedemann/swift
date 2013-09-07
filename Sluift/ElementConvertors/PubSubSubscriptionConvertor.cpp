/*
 * Copyright (c) 2013 Remko Tronçon
 * Licensed under the GNU General Public License.
 * See the COPYING file for more information.
 */

#include <Sluift/ElementConvertors/PubSubSubscriptionConvertor.h>

#include <lua.hpp>
#include <boost/smart_ptr/make_shared.hpp>


#include <Sluift/LuaElementConvertors.h>

#pragma clang diagnostic ignored "-Wunused-private-field"

using namespace Swift;

PubSubSubscriptionConvertor::PubSubSubscriptionConvertor(LuaElementConvertors* convertors) : 
		GenericLuaElementConvertor<PubSubSubscription>("pubsub_subscription"),
		convertors(convertors) {
}

PubSubSubscriptionConvertor::~PubSubSubscriptionConvertor() {
}

boost::shared_ptr<PubSubSubscription> PubSubSubscriptionConvertor::doConvertFromLua(lua_State* L) {
	boost::shared_ptr<PubSubSubscription> result = boost::make_shared<PubSubSubscription>();
	lua_getfield(L, -1, "node");
	if (lua_isstring(L, -1)) {
		result->setNode(std::string(lua_tostring(L, -1)));
	}
	lua_pop(L, 1);
	lua_getfield(L, -1, "subscriptionid");
	if (lua_isstring(L, -1)) {
		result->setSubscriptionID(std::string(lua_tostring(L, -1)));
	}
	lua_pop(L, 1);
	lua_getfield(L, -1, "jid");
	if (lua_isstring(L, -1)) {
		result->setJID(JID(std::string(lua_tostring(L, -1))));
	}
	lua_pop(L, 1);
	lua_getfield(L, -1, "options");
	if (!lua_isnil(L, -1)) {
		if (boost::shared_ptr<PubSubSubscribeOptions> payload = boost::dynamic_pointer_cast<PubSubSubscribeOptions>(convertors->convertFromLuaUntyped(L, -1, "pubsub_subscribe_options"))) {
			result->setOptions(payload);
		}
	}
	lua_pop(L, 1);
	lua_getfield(L, -1, "subscription");
	lua_pop(L, 1);
	return result;
}

void PubSubSubscriptionConvertor::doConvertToLua(lua_State* L, boost::shared_ptr<PubSubSubscription> payload) {
	lua_createtable(L, 0, 0);
	if (payload->getNode()) {
		lua_pushstring(L, (*payload->getNode()).c_str());
		lua_setfield(L, -2, "node");
	}
	if (payload->getSubscriptionID()) {
		lua_pushstring(L, (*payload->getSubscriptionID()).c_str());
		lua_setfield(L, -2, "subscriptionid");
	}
	lua_pushstring(L, payload->getJID().toString().c_str());
	lua_setfield(L, -2, "jid");
	if (convertors->convertToLuaUntyped(L, payload->getOptions()) > 0) {
		lua_setfield(L, -2, "options");
	}
	switch (payload->getSubscription()) {
		case PubSubSubscription::None:
			lua_pushstring(L, "none");
			break;
		case PubSubSubscription::Pending:
			lua_pushstring(L, "pending");
			break;
		case PubSubSubscription::Subscribed:
			lua_pushstring(L, "subscribed");
			break;
		case PubSubSubscription::Unconfigured:
			lua_pushstring(L, "unconfigured");
			break;
	}
	lua_setfield(L, -2, "subscription");
}