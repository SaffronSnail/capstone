#! /bin/guile \
-e main -s
!#

(add-to-load-path (dirname (dirname (current-filename))))
(display %load-path) (newline)

(use-modules (saffronsnail butler)
             (saffronsnail log)
             (ice-9 getopt-long)
)

(define (main args)
  (define option-spec
    '((port (single-char #\p) (value #t)))
  )
  (define options (getopt-long (command-line) option-spec))
  (logmsg "staring the main program...")
  (let ((port (option-ref options 'port #f)))
    (if port
      (run-butler-listener port)
      (run-butler-listener)
    )
  )
)

