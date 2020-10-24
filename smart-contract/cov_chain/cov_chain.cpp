#include "/home/vex/Documents/covchain_backend/contract/VEXANIUM/CONTRACTS_DIR/cov_chain/cov_chain.hpp"

[[eosio::action]] 
void cov_chain::make(uint64_t chain_id,uint64_t user_id , string name, string roles,string date,string action,string location,string temp,string instance,string description) {
   chaintable.emplace( _self, [&]( auto& u ) {
            u.history_id = chaintable.available_primary_key();
            u.chain_id = chain_id;
            u.user_id = user_id;
            u.name = name;
            u.roles = roles;
            u.date = date;
            u.action = action;
            u.location = location;
            u.temp = temp;
            u.instance = instance;
            u.description = description;
   });
}

// INPUT EXAMPLE BELOW
// ./cleos --url https://explorer.vexanium.com:6960 push action sertifigo123 set '[111,"KEVIN","Impostor","16 03 02","Kill","Medbay","-36Cel","Btch","Scan and kill"]' -p sertifigo123

[[eosio::action]] 
void cov_chain::getdetail( uint64_t history_id ) {
   auto itr = chaintable.find(history_id);
   check( itr != chaintable.end(), "user does not exist in table" );
   // json data = {
   //    "history_id":itr->history_id,
   //    "user_id":itr->user_id,
   //    "chain_id":itr->chain_id,
   //    "name":itr->name,
   //    "roles":itr->roles,
   //    "date":itr->date,
   //    "action":itr->action,
   //    "location":itr->location,
   //    "temp":itr->temp,
   //    "instance":itr->instance,
   //    "description":%
   // };

   // eosio::print_f("{'history_id':%,'user_id':%,'chain_id':%,'name':%,'roles':%,'date':%,'action':%,'location':%,'temp':%,'instance':%,'description':%}", itr->history_id, itr->user_id, itr->chain_id, itr->name, itr->roles, itr->date, itr->action, itr->location, itr->temp, itr->instance, itr->description );

   eosio::print_f("[%,%,%,%,%,%,%,%,%,%,%]**", itr->history_id, itr->user_id, itr->chain_id, itr->name, itr->roles, itr->date, itr->action, itr->location, itr->temp, itr->instance, itr->description );
}

[[eosio::action]] 
void cov_chain::getchain( uint64_t chain_id ) {
   auto idx = chaintable.get_index<"secid"_n>();
   for ( auto itr = idx.begin(); itr != idx.end(); itr++ ) {
      if (itr->chain_id == chain_id)
      {
         getdetail(itr->history_id);
      }
      
      
      
   }
}

[[eosio::action]] 
void cov_chain::gethistory( uint64_t user_id ) {
   auto idx = chaintable.get_index<"secid"_n>();
   for ( auto itr = idx.begin(); itr != idx.end(); itr++ ) {
      if (itr->user_id == user_id)
      {
         getdetail(itr->history_id);
      }
      
      
   }
}

[[eosio::action]] 
void cov_chain::mod( uint64_t history_id, uint64_t chain_id ) {
   auto itr = chaintable.find(history_id);
   check( itr != chaintable.end(), "user does not exist in table" );
   chaintable.modify( itr, _self, [&]( auto& row ) {
      row.chain_id = chain_id;
   });
}

[[eosio::action]]
void cov_chain::del( uint64_t history_id ) {
  // check if the user already exists
  auto itr = chaintable.find(history_id );
  if ( itr == chaintable.end() ) {
    printf("user does not exist in table, nothing to delete" );
    return;
  }

  // if we got so far it means user exists so we can delete it using 
  // the iterator found based on its primary key
  chaintable.erase( itr );
}
