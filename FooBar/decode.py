import base64
encrypted="C1UWFgoZCxZdUU9TRFcVFwYIDklJDlEMBggcFwQEHB9JRRRWSAwXBBcADgweSUkOUQoPAh8AERBO\nWlRFCR8BChYVFgwBBR9JSQ5RDgoMGRcTBgQfABEJVlVJQwUcCQwKEQsBCVpPThYREAcKHQlJRRRWSBoFFhdCT0ldCApBUU9TRFcFDA1IXRM="
my_eyes=str.encode("precizne.void")
decoded=base64.b64decode(encrypted)
decrypted=""
for i in range(0,len(decoded)):
    decrypted += chr((my_eyes[i % len(my_eyes)] ^ decoded[i]))
print(decrypted)
