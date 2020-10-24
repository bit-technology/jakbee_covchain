#include <eosio/eosio.hpp>
using namespace eosio;
using namespace std;

class [[eosio::contract]] cov_chain : public contract {
   public:
      using contract::contract;
      cov_chain( name receiver, name code, datastream<const char*> ds )
         : contract(receiver, code, ds), tablechain(receiver, receiver.value) {}


         struct [[eosio::table]] table_chain {
            uint64_t history_id;
            uint64_t chain_id;
            string name;
            string roles;
            string date;
            string action;
            string location;
            string temp;
            string instance;
            string description;
            auto primary_key()const { return history_id;}
            uint64_t get_chain()const { return chain_id; }
        };

      typedef eosio::multi_index<"tablechain"_n, table_chain, eosio::indexed_by<"secid"_n, eosio::const_mem_fun<table_chain, uint64_t, &table_chain::get_chain>>> table_chains;

      table_chains tablechain;

      [[eosio::action]] 
      void make(uint64_t chain_id, string name, string roles,string date,string action,string location,string temp,string instance,string description);
      [[eosio::action]] 
      void getdetail( uint64_t history_id );
      [[eosio::action]] 
      void getchain( uint64_t chain_id );
      [[eosio::action]] 
      void mod( uint64_t history_id, uint64_t chain_id );
      [[eosio::action]] 
      void del( uint64_t history_id );

      using make_action = action_wrapper<"make"_n, &cov_chain::make>;
      using getdetail_action = action_wrapper<"getdetail"_n, &cov_chain::getdetail>;
      using getchain_action = action_wrapper<"getchain"_n, &cov_chain::getchain>;
      using mod_action = action_wrapper<"mod"_n, &cov_chain::mod>;
      using del_action = action_wrapper<"del"_n, &cov_chain::del>;
};
