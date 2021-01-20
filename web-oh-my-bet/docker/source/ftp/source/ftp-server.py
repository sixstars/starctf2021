from pyftpdlib.authorizers import DummyAuthorizer
from pyftpdlib.handlers import FTPHandler
from pyftpdlib.servers import FTPServer


authorizer = DummyAuthorizer()

authorizer.add_user("fan", "root", ".",perm="elrafmwMT")
authorizer.add_anonymous(".")

handler = FTPHandler
handler.permit_foreign_addresses = True
handler.passive_ports = range(2000, 2030)
handler.authorizer = authorizer

server = FTPServer(("172.20.0.2", 8877), handler)
server.serve_forever()

