#Asil Elsharafi, Faiza Amoodi

from Crypto.Hash import SHA256
from Crypto.PublicKey import ECC
from Crypto.Signature import DSS

key = ECC.import_key(open('pubkey.der').read())
h = SHA256.new(received_message)
verifier = DSS.new(key, 'fips-186-3')

try:
    verifier.verify(h, signature)
    print("The message is authentic.")
except ValueError:
    print("The message is not authentic.")
