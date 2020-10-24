#include <eosio/asset.hpp>
#include <eosio/eosio.hpp>
#include <eosio/transaction.hpp>
#include <eosio/crypto.hpp>
#include <vector>

using namespace std;
using namespace eosio;

class [[eosio::contract]] cov_chain : public eosio::contract {
  private:

    struct [[eosio::table]] designerChain {
        uint64_t historyId;
        uint64_t chainId;
        string name;
        string roles;
        string date;
        string action;
        string location;
        string temp;
        string composition;
        uint64_t draft;
        string devTeam;
        string instance;
        string description;
        auto primary_key()const { return historyId;}
    };
    
    struct [[eosio::table]] regulatorChain {
        uint64_t historyId;
        uint64_t chainId;
        string name;
        string roles;
        string date;
        string action;
        string location;
        string temp;
        string country;
        string instance;
        bool approved;
        string vaccineType;
        string description;
        auto primary_key()const { return historyId;}
    };

    struct [[eosio::table]] hospitalChain {
        uint64_t historyId;
        uint64_t chainId;
        string name;
        string roles;
        string date;
        string action;
        string location;
        string temp;
        string address;
        string instance;
        string vaccineType;
        string description;
        auto primary_key()const { return historyId;}
    };
    
    typedef eosio::multi_index<name("designer"), designerChain> designer;
    typedef eosio::multi_index<name("regulator"), regulatorChain> regulator;  
    typedef eosio::multi_index<name("hospital"), hospitalChain> hospital;  

    designer _designer;
    regulator _regulator;
    hospital _hospital;

  public:
    using contract::contract;

    cov_chain( name receiver, name code, datastream<const char*> ds ): contract(receiver, code, ds),
                       _designer(receiver, receiver.value),
                       _regulator(receiver, receiver.value),
                       _hospital(receiver, receiver.value){}
    
    checksum256 get_trx_id() {
        size_t size = transaction_size();
        char buf[size];
        size_t read = read_transaction( buf, size );
        check( size == read, "read_transaction Error");
        return sha256(buf, read); 
    }
    
                       
    [[eosio::action]]
    void designerinp(string name, uint64_t chainId, string roles, string date, string action, string location, string temp, string composition, uint64_t draft, string devTeam, string instance, string description) {

      _designer.emplace(_self, [&](auto& row) {
          row.historyId = _designer.available_primary_key();
          row.chainId = chainId;
          row.name = name;
          row.roles = roles;
          row.date = date;
          row.action = action;
          row.location = location;
          row.temp = temp;
          row.composition = composition;
          row.draft = draft;
          row.devTeam = devTeam;
          row.instance = instance;
          row.description = description;
      }); 
    }
    
};