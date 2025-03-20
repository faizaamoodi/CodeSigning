#Asil Elsharafi, Faiza Amoodi

from Crypto.Hash import SHA256
from Crypto.PublicKey import ECC
from Crypto.Signature import DSS
from product import signature

#private key generation ?? 

#function to receive public key + message

#intialize key val and import public key through file
key = ECC.import_key(open('pubkey.der').read())

#create new hash of message
h = SHA256.new(received_message)

#generate the DSS verification using key
validator = DSS.new(key, 'fips-186-3')

#function to match signatures
try:
    validator.verify(h, signature)
    print("Code certificate valid: execution allowed")
except ValueError:
    print("Code certificate invalid: execution denied")
