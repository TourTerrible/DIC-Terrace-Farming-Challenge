import http.server
import socketserver



PORT = 8080
Handler = http.server.SimpleHTTPRequestHandler

with socketserver.TCPServer(("10.150.32.160", PORT), Handler) as httpd:
    print("serving at port", PORT)
    httpd.serve_forever()
