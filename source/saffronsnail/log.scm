(define-module (saffronsnail log))

(define-public (logmsg message)
  (display (current-thread)) (display ": ") (display message) (newline)
)

