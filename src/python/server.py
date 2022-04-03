from http.server import BaseHTTPRequestHandler, HTTPServer
from datetime import datetime

hostName = "127.0.0.1"
serverPort = 8080

class Server(BaseHTTPRequestHandler):
  def do_GET(self):
    time = datetime.now().strftime("%d/%m/%Y %H:%M:%S")

    self.send_response(200)
    self.send_header("Content-type", "text/plain")
    self.end_headers()
    self.wfile.write(bytes(f"Hello world! The time is {time} and you requested the path {self.path}", "utf-8"))
  
  def log_message(self, format, *args):
    # Silence the default server logging
    return

if __name__ == "__main__":        
  webServer = HTTPServer((hostName, serverPort), Server)
  print("Listening on http://%s:%s" % (hostName, serverPort))

  try:
    webServer.serve_forever()
  except KeyboardInterrupt:
    pass

  webServer.server_close()