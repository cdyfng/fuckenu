eosname1=`sed '/^eosname1=/!d;s/.*=//' config`
eosname2=`sed '/^eosname2=/!d;s/.*=//' config`
pswd=`sed '/^pswd=/!d;s/.*=//' config`
echo $eosname1
echo $eosname2
echo $pswd

#cleos wallet unlock -n main_wallet --password $(cat ~/main_wallet_password.txt)
#cleos -u 'https://api.eosnewyork.io' set contract $eosname1  ./fuckenu/ -p $eosname1@active
#cleos -u 'https://api.eosnewyork.io'  push action $eosname1 init '["'$eosname1'"]'  -p $eosname1@active
#cleos -u 'https://api.eosnewyork.io'  push action $eosname1 setting '["eidosonecoin", "0.0001 EOS", "No memo"]'  -p $eosname1@active
cleos -u 'https://api.eosnewyork.io'  push action $eosname1 run '["'$eosname1'"]'  -p $eosname1@active

#cleos -u 'https://api.eosnewyork.io'  push action $eosname1 stop '["'$eosname1'"]'  -p $eosname1@active