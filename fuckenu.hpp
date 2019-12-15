#include <eosio/eosio.hpp>
#include <eosio/asset.hpp>
#include <eosio/singleton.hpp>
#include <eosio/transaction.hpp>

using namespace std;
using namespace eosio;

#define EOS_SYMBOL symbol("EOS", 4)


CONTRACT fuckenu : public contract
{
public:
    //using contract::contract;

    fuckenu(name receiver, name code, datastream<const char *> ds) : contract(receiver, code, ds),
                                                                     _global(receiver, receiver.value){};

    ACTION start();
    ACTION stop();
    ACTION init();
    ACTION run();
    ACTION setting(name to, asset quantity, string memo);

private:
    struct [[ eosio::table("global"), eosio::contract("fuckenu") ]] st_global
    {
        uint64_t current_id;
        name to;
        asset quantity;
        string memo;
        bool status;

        uint64_t primary_key() const { return current_id; }
    };
    typedef singleton<name("global"), st_global> tb_global;

    tb_global _global;

    uint64_t next_id()
    {
        st_global global = _global.get_or_default();
        global.current_id += 1;
        _global.set(global, _self);
        return global.current_id;
    }

    template <typename... Args>
    void send_defer_action(Args && ... args)
    {
        transaction trx;
        trx.actions.emplace_back(std::forward<Args>(args)...);
        trx.delay_sec = 10;
        trx.send(next_id(), _self, false);
    }
};