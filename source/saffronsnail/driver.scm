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
    '((send-port (value #t)))
    '((recv-port (value #t)))
    '((once (single-char #\o)))
    '((version (single-char #\v)))
    '((help (single-char #\h)))
  )
  (define options (getopt-long (command-line) option-spec))

  (case
    ((option-ref options 'version #f) (display "Butler 0.1") (newline)
                                      (display "Copyright (C) 2017 Bryan Ferris") (newline)
                                      (display "License LLGPL; Lisp Lesser General Public License") (newline)
                                      (display "This is free software; you are free to change and redistribute it.") (newline)
                                      (display "There is NO WARRANTY, to the extent permitted by law") (newline)
    )
    ((option-ref options 'help    #f)
     (display "Useage: driver.scm [--send-port port-number] [--recv-port port-number] [--once]") (newline)
     (display "Report bugs to: saffronsnail@hushmail.com") (newline)
     (display "Pkg home page: https://github.com/saffronsnail/capstone") (newline)
    )
    (else
      (let ((port (option-ref options 'port #f))
            (once (option-ref options 'once #f))
           )
        (if port
          (run-butler-listener port #:run-continuous? (not once))
          (run-butler-listener #:run-continuous? (not once))
        )
      )
    )
)

