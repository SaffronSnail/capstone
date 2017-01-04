(define-module (saffronsnail butler glue)
               #:export (attendant-name receive-entrance-request send-entrance-request)
)

(use-modules (system foreign))

(define impl (dynamic-link "libbutler"))

(define attendant-name-impl
  (pointer->procedure '* (dynamic-func "get_attendant_name" impl)
                                       (list '*))
)

(define (attendant-name entrance-request)
  (pointer->string (attendant-name-impl entrance-request))
)

(define receive-entrance-request
  (pointer->procedure '* (dynamic-func "receive_entrance_request" impl)
                      (list unsigned-int)
  )
)

(define send-entrance-request-impl
  (pointer->procedure int (dynamic-func "send_entrance_request" impl)
                      (list '* unsigned-int '* unsigned-int)
  )
)

(define (send-entrance-request server-name server-port attendant-name local-port)
  (send-entrance-request-impl (string->pointer server-name) server-port (string->pointer attendant-name) local-port)
)

(define port
  (pointer->procedure unsigned-int (dynamic-func "get_port" impl)
                      (list unsigned-int)
  )
)

(define send-entrance-response
  (pointer->procedure void (dynamic-func "send_entrance_response" impl)
                      (list '* unsigned-int)
  )
)

(define receive-entrance-response
  (pointer->procedure '* (dynamic-func "receive_entrance_response" impl)
                      (list unsigned-int)
  )
)

