#Asil Elsharafi, Faiza Amoodi

from Crypto.Hash import SHA256
from Crypto.PublicKey import ECC
from Crypto.Signature import DSS

#function to receive public key + message

#intialize key val and import public key thorugh file
key = ECC.import_key(open('pubkey.der').read())

#create new hash of message
h = SHA256.new(received_message)

#generate the DSS verification using key
verifier = DSS.new(key, 'fips-186-3')

#function to match signatures
try:
    verifier.verify(h, signature)
    print("The message is authentic.")
except ValueError:
    print("The message is not authentic.")
