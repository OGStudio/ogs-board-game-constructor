#!/usr/bin/env python

# This is a simple HTTP server with enabled Cross-Origin Resource Sharing (CORS).

# Topic: Enable access control on simple HTTP server
# Source: https://stackoverflow.com/a/21957017/3404710

# Python 3.
try:
    from http.server import HTTPServer
    from http.server import SimpleHTTPRequestHandler
    from http.server import test as test_orig
    import sys

    def test(*args):
        port = 8000
        if len(sys.argv) > 1:
            port = int(sys.argv[1])
        test_orig(*args, port = port)

# Python 2.
except ImportError:
    from BaseHTTPServer import HTTPServer
    from BaseHTTPServer import test
    from SimpleHTTPServer import SimpleHTTPRequestHandler

class CORSRequestHandler(SimpleHTTPRequestHandler):
    def end_headers(self):
        self.send_header('Access-Control-Allow-Origin', '*')
        SimpleHTTPRequestHandler.end_headers(self)

if __name__ == '__main__':
    test(CORSRequestHandler, HTTPServer)

