/* automatically generated by pepy 8.0 #2 (pilsen), do not edit! */

#include "psap.h"

#ifndef lint
static char *pepyid = "pepy 8.0 #2 (pilsen) of Thu Jul  2 10:07:03 MET DST 1992";
#endif

void	advise ();

/* Generated from module KM */
# line 3 "CADB.py"
      /* surrounding global definitions       */
#include        "cadb.h"

#ifndef PEPYPARM
#define PEPYPARM char *
#endif /* PEPYPARM */
extern PEPYPARM NullParm;

/* ARGSUSED */

int	build_KM_IssuedCertificate (pe, explicit, len, buffer, parm)
register PE     *pe;
int	explicit;
int	len;
char   *buffer;
IssuedCertificate * parm;
{
    PE	p0_z = NULLPE;
    register PE *p0 = &p0_z;

    if (((*pe) = pe_alloc (PE_CLASS_UNIV, PE_FORM_CONS, PE_CONS_SEQ)) == NULLPE) {
        advise (NULLCP, "IssuedCertificate: %s", PEPY_ERR_NOMEM);
        return NOTOK;
    }
    (*p0) = NULLPE;

    {	/* serial */
        register integer p1 = parm -> serial ;

        if (((*p0) = num2prim (p1, PE_CLASS_UNIV, PE_PRIM_INT)) == NULLPE) {
            advise (NULLCP, "serial: %s", PEPY_ERR_NOMEM);
            return NOTOK;
        }

#ifdef DEBUG
        (void) testdebug ((*p0), "serial");
#endif

    }

    if ((*p0) != NULLPE)
        if (seq_add ((*pe), (*p0), -1) == NOTOK) {
            advise (NULLCP, "IssuedCertificate %s%s", PEPY_ERR_BAD_SEQ,
                    pe_error ((*pe) -> pe_errno));
            return NOTOK;
        }
    (*p0) = NULLPE;

    {	/* issuedate */
        if (build_UNIV_UTCTime (p0, 0, NULL, parm->date_of_issue , NullParm) == NOTOK)
            return NOTOK;

#ifdef DEBUG
        (void) testdebug ((*p0), "issuedate");
#endif

    }

    if ((*p0) != NULLPE)
        if (seq_add ((*pe), (*p0), -1) == NOTOK) {
            advise (NULLCP, "IssuedCertificate %s%s", PEPY_ERR_BAD_SEQ,
                    pe_error ((*pe) -> pe_errno));
            return NOTOK;
        }

#ifdef DEBUG
    (void) testdebug ((*pe), "KM.IssuedCertificate");
#endif


    return OK;
}

/* ARGSUSED */

int	build_KM_IssuedCertificateSet (pe, explicit, len, buffer, parm)
register PE     *pe;
int	explicit;
int	len;
char   *buffer;
SET_OF_IssuedCertificate * parm;
{
    PE	p2 = NULLPE;
    PE	p3_z = NULLPE;
    register PE *p3 = &p3_z;

    if (((*pe) = pe_alloc (PE_CLASS_UNIV, PE_FORM_CONS, PE_CONS_SET)) == NULLPE) {
        advise (NULLCP, "IssuedCertificateSet: %s", PEPY_ERR_NOMEM);
        return NOTOK;
    }
    for (; parm; parm = parm -> next) {
        if (build_KM_IssuedCertificate (p3, 0, NULL, NULLCP, parm -> element ) == NOTOK)
            return NOTOK;

#ifdef DEBUG
        (void) testdebug ((*p3), "member");
#endif

        (void) set_addon ((*pe), p2, (*p3));
        p2 = (*p3);
    }

#ifdef DEBUG
    (void) testdebug ((*pe), "KM.IssuedCertificateSet");
#endif


    return OK;
}

/* ARGSUSED */

int	parse_KM_IssuedCertificate (pe, explicit, len, buffer, parm)
register PE	pe;
int	explicit;
int    *len;
char  **buffer;
IssuedCertificate ** parm;
{
    register PE p4;

#ifdef DEBUG
    (void) testdebug (pe, "KM.IssuedCertificate");
#endif

    if (explicit) {
        if (pe -> pe_class != PE_CLASS_UNIV
                || pe -> pe_form != PE_FORM_CONS
                || pe -> pe_id != PE_CONS_SEQ) {
            advise (NULLCP, "IssuedCertificate bad class/form/id: %s/%d/0x%x",
                    pe_classlist[pe -> pe_class], pe -> pe_form, pe -> pe_id);
            return NOTOK;
        }
    }
    else
        if (pe -> pe_form != PE_FORM_CONS) {
            advise (NULLCP, "IssuedCertificate bad form: %d", pe -> pe_form);
            return NOTOK;
        }

    {
# line 46 "CADB.py"

            if ((*(parm) = (IssuedCertificate *)
                    calloc (1, sizeof **(parm))) == ((IssuedCertificate *) 0)) {
                advise (NULLCP, "out of memory");
                return NOTOK;
            }
        
    }
    if ((p4 = prim2seq (pe)) == NULLPE) {
        advise (NULLCP, "IssuedCertificate %s%s", PEPY_ERR_BAD_SEQ,
                pe_error (pe -> pe_errno));
        return NOTOK;
    }
    pe = p4;

    {
        register PE p5;

        if ((p5 = first_member (pe)) != NULLPE) {
            p4 = p5;

            {	/* serial */
                register integer p6;

#ifdef DEBUG
                (void) testdebug (p5, "serial");
#endif

                if (p5 -> pe_class != PE_CLASS_UNIV
                        || p5 -> pe_form != PE_FORM_PRIM
                        || p5 -> pe_id != PE_PRIM_INT) {
                    advise (NULLCP, "serial bad class/form/id: %s/%d/0x%x",
                            pe_classlist[p5 -> pe_class], p5 -> pe_form, p5 -> pe_id);
                    return NOTOK;
                }

                if ((p6 = prim2num (p5)) == NOTOK
                        && p5 -> pe_errno != PE_ERR_NONE) {
                    advise (NULLCP, "serial %s%s", PEPY_ERR_BAD_INTEGER,
                            pe_error (p5 -> pe_errno));
                    return NOTOK;
                }
                (*parm)->serial  = p6;
            }
        }
        else {
            advise (NULLCP, "IssuedCertificate %sserial element", PEPY_ERR_MISSING);
            return NOTOK;
        }

    }

    {
        register PE p7;

        if ((p7 = (pe != p4 ? next_member (pe, p4) : first_member (pe))) != NULLPE) {
            p4 = p7;

            {	/* issuedate */
#ifdef DEBUG
                (void) testdebug (p7, "issuedate");
#endif

                if (parse_UNIV_UTCTime (p7, 1, NULLIP, &((*parm)->date_of_issue ), NullParm) == NOTOK)
                    return NOTOK;
            }
        }
        else {
            advise (NULLCP, "IssuedCertificate %sissuedate element", PEPY_ERR_MISSING);
            return NOTOK;
        }

    }


    if (pe -> pe_cardinal > 2) {
        advise (NULLCP, "IssuedCertificate %s(2): %d", PEPY_ERR_TOO_MANY_ELEMENTS,
                pe -> pe_cardinal);
        return NOTOK;
    }

    return OK;
}

/* ARGSUSED */

int	parse_KM_IssuedCertificateSet (pe, explicit, len, buffer, parm)
register PE	pe;
int	explicit;
int    *len;
char  **buffer;
SET_OF_IssuedCertificate ** parm;
{
    register PE p8;

#ifdef DEBUG
    (void) testdebug (pe, "KM.IssuedCertificateSet");
#endif

    if (explicit) {
        if (pe -> pe_class != PE_CLASS_UNIV
                || pe -> pe_form != PE_FORM_CONS
                || pe -> pe_id != PE_CONS_SET) {
            advise (NULLCP, "IssuedCertificateSet bad class/form/id: %s/%d/0x%x",
                    pe_classlist[pe -> pe_class], pe -> pe_form, pe -> pe_id);
            return NOTOK;
        }
    }
    else
        if (pe -> pe_form != PE_FORM_CONS) {
            advise (NULLCP, "IssuedCertificateSet bad form: %d", pe -> pe_form);
            return NOTOK;
        }

    if ((p8 = prim2set (pe)) == NULLPE) {
        advise (NULLCP, "IssuedCertificateSet %s%s", PEPY_ERR_BAD_SET,
                pe_error (pe -> pe_errno));
        return NOTOK;
    }
    pe = p8;

    for (p8 = first_member (pe); p8; p8 = next_member (pe, p8)) {
        {
# line 67 "CADB.py"

                if ((*(parm) = (SET_OF_IssuedCertificate *)
                        calloc (1, sizeof **(parm))) == ((SET_OF_IssuedCertificate *) 0)) {
                    advise (NULLCP, "out of memory");
                    return NOTOK;
                }
            
        }
        {
#ifdef DEBUG
            (void) testdebug (p8, "member");
#endif

            if (parse_KM_IssuedCertificate (p8, 1, NULLIP, NULLVP, &((*parm) -> element)) == NOTOK)
                return NOTOK;
            {
# line 76 "CADB.py"
 parm = &((*parm) -> next); 
            }
        }
    }

    return OK;
}