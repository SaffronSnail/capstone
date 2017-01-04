(define-module (saffronsnail butler)
               #:export (run-butler-listener)
               #:use-module (saffronsnail attendant)
               #:use-module (saffronsnail butler glue)
               #:use-module (saffronsnail butler log)
)

; this is the 'main' of this file; it waits for someone to connect, reads the
; attendant request, and migrates the connection to a different port so that
; it can continue listening; there is currently no 'clean' way to close this,
; just ctrl-c at the terminal
(define* (run-butler-listener #:key (port 8080))
  (entrance-protocol (receive-entrance-request port))
  (run-butler-listener #:port port)
)

; the entrance protocol defines what happens when a user first makes contact
; with butler; it involves determining what attendant should serve this
; connection and what port the user will be speaking to for the rest of the
; connection
(define (entrance-protocol entrance-request)
  (log "Got a connection! Attendant requested: " (attendant-name entrance-request))

  (let ((attendant (make-attendant (attendant-name entrance-request))))
    (call-with-new-thread (attendant 'start))
    (send-entrance-response entrance-request (attendant 'port))
  )
)

