; This module loads functions from libbutler for other guile scripts to use; for
; details on the functions defined here, refer to the documentation in
; entrance-protocol.h

(define-module (saffronsnail butler glue))

(use-modules (system foreign))

(define impl (dynamic-link "libbutler"))

(define-public attendant-name-impl
  (pointer->procedure '* (dynamic-func "get_attendant_name" impl)
                                       (list '*))
)

(define-public (attendant-name entrance-request)
  (pointer->string (attendant-name-impl entrance-request))
)

(define-public receive-entrance-request
  (pointer->procedure '* (dynamic-func "receive_entrance_request" impl)
                      (list unsigned-int)
  )
)

(define-public send-entrance-request-impl
  (pointer->procedure int (dynamic-func "send_entrance_request" impl)
                      (list unsigned-int '* unsigned-int '* unsigned-int)
  )
)

(define-public (send-entrance-request send-port server-name server-port
                                      attendant-name local-port
               )
  (send-entrance-request-impl send-port (string->pointer server-name)
                              server-port (string->pointer attendant-name)
                              local-port
  )
)

(define-public port
  (pointer->procedure unsigned-int (dynamic-func "get_port" impl)
                      '(*)
  )
)

(define-public send-entrance-response
  (pointer->procedure void (dynamic-func "send_entrance_response" impl)
                      (list unsigned-int '* unsigned-int)
  )
)

(define-public receive-entrance-response
  (pointer->procedure '* (dynamic-func "receive_entrance_response" impl)
                      (list unsigned-int)
  )
)

