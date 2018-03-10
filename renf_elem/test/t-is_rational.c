/*
    Copyright (C) 2017 Vincent Delecroix

    This file is part of e-antic

    e-antic is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/


#include <e-antic/renf_elem.h>

int main()
{
    int iter;
    FLINT_TEST_INIT(state);

    printf("is_rational....");
    fflush(stdout);

    for (iter = 0; iter < 50; iter++)
    {
        renf_t nf;
        fmpq_t x;
        renf_elem_t a;

        renf_randtest(nf, state, 2 + n_randint(state, 20), 20 + n_randint(state, 30));

        fmpq_init(x);
        fmpq_randtest(x, state, 10 + n_randint(state, 30));

        renf_elem_init(a, nf);
        renf_elem_set_fmpq(a, x, nf);

        if (!renf_elem_is_rational(a, nf))
        {
            printf("FAIL:\n");
            flint_abort();
        }

        fmpq_clear(x);
        renf_elem_clear(a, nf);

        if (!(nf->nf->flag & NF_LINEAR))
        {
            fmpq_poly_t p;
            renf_elem_t a;

            fmpq_poly_init(p);
            fmpq_poly_set_coeff_si(p, 1, 1);

            renf_elem_init(a, nf);
            renf_elem_set_fmpq_poly(a, p, nf);

            if (renf_elem_is_rational(a, nf))
            {
                printf("FAIL:\n");
                flint_abort();
            }

            fmpq_poly_clear(p);
            renf_elem_clear(a, nf);
        }
    }

    FLINT_TEST_CLEANUP(state);
    printf("PASS\n");
    return 0;
}
