#include "fuckenu.hpp"

ACTION fuckenu::stop()
{
    require_auth(get_self());
    st_global global = _global.get_or_default();
    global.status = 0;
    _global.set(global, _self);
}

ACTION fuckenu::start()
{
    require_auth(get_self());
    st_global global = _global.get_or_default();
    global.status = 1;
    _global.set(global, _self);
}

ACTION fuckenu::setting(name to, asset quantity, string memo)
{
    require_auth(get_self());
    st_global global = _global.get_or_default();
    global.to = to;
    global.quantity = quantity;
    global.memo = memo;
    _global.set(global, _self);
}
ACTION fuckenu::run()
{
    require_auth(get_self());
    st_global global = _global.get_or_default();
    //每次40个action
    for (int a = 0; a <= 40; a = a + 1)
    {
        action(permission_level{_self, "active"_n},
               "eosio.token"_n,
               "transfer"_n,
               std::make_tuple(_self, global.to, global.quantity, std::to_string(a)))
            .send();
    }
    //判断是否继续发送
    if (global.status)
    {
        send_defer_action(permission_level{_self, "active"_n},
                          _self,
                          "run"_n,
                          std::make_tuple());
    }
}
ACTION fuckenu::init()
{
    require_auth(get_self());
    st_global global = _global.get_or_default();
    global.current_id = 0;
    global.to = "eidosonecoin"_n;
    global.quantity = asset(1, EOS_SYMBOL);
    global.status = 1;
    global.memo = std::string("");
    _global.set(global, _self);
}
