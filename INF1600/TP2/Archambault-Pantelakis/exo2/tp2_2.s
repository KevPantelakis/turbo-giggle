.global func_s

func_s:
    flds g
    flds d
    faddp
    fstps a
    flds b
    flds c
    fmulp
    flds a
    fdivp
    fstps a
    flds f
    flds c
    fsubrp
    flds e
    fdivp
    flds a
    fmulp
    fstps a
    flds g
    flds d
    faddp
    flds b
    fmulp
    flds a
    fsubp
    fstps a
    ret
