package main

import (
	"fmt"
	"net/http"
	"time"
	"os"
	"io"
)

func requestListener(w http.ResponseWriter, req *http.Request) {	
	path := req.URL.Path
	currentTime := time.Now().Format("2006-01-02 15:04:05")
	formatedString := fmt.Sprintf("Hello world! The time is %s and you requested the path %s", currentTime, path)

	w.Header().Set("Content-Type", "text/plain")
	fmt.Fprintf(w, formatedString)
}

func main() {
	port := 8080
	
	io.WriteString(os.Stdout, fmt.Sprintf("Listening on http://127.0.0.1:%d\n", port))

	http.HandleFunc("/", requestListener)

	http.ListenAndServe(fmt.Sprintf(":%d", port), nil)
}