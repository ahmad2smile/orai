## Compiler

A long natural language string (Statement) would be the input. So oppose to traditional compilers where keywords would
have one to many relation with Instructions, this compilation would have many to one and possibly many to many relation.

### Grammar

Compiler has basic operator grammar. But plugins would have to provide their own.

Potential Issue:

- Conflict with base grammar, since input would be just natural language string a stopping indicator for plugin's
grammar would've been base compiler's token, but Plugin might make use of that. Obvious solution to restrict plugin's
from using those would not be ideal as whole statement for end user should not seem restrictive.