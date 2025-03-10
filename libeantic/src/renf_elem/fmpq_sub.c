/*
    Copyright (C) 2016 Vincent Delecroix

    This file is part of e-antic

    e-antic is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 3.0 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/

#include "../../e-antic/config.h"

#include "../../e-antic/renf_elem.h"

static void arb_fmpq_sub(arb_t a, const fmpq_t c, const arb_t b, slong prec)
{
    arb_t x;
    arb_init(x);
    arb_set_fmpq(x, c, prec);
    arb_sub(a, x, b, prec);
    arb_clear(x);
}

void renf_elem_fmpq_sub(renf_elem_t a, const fmpq_t c, const renf_elem_t b, const renf_t nf)
{
    nf_elem_fmpq_sub(a->elem, c, b->elem, nf->nf);
    arb_fmpq_sub(a->emb, c, b->emb, nf->prec);
}
