#include </usr/local/Cellar/python3/3.6.4_2/Frameworks/Python.framework/Versions/3.6/include/python3.6m/Python.h>
#include "scws.h"
#include <string.h>

typedef struct {
    PyObject_HEAD
    scws_t * st;
} PyScws;

scws_t s;
static PyObject * scws_scws_new(PyObject * self,PyObject * args){
    if (!(s = scws_new())) {
        return NULL;
    }
    return Py_BuildValue("i",1);
}

static PyObject * scws_set_xdb(PyObject * self,PyObject * args){
    const char * xdb;
    if (!PyArg_ParseTuple(args, "s",&xdb)){
        return NULL;
    }
    scws_set_dict(s, xdb, SCWS_XDICT_XDB);
    return Py_BuildValue("i",1);
}
static PyObject * scws_set_txt(PyObject * self,PyObject * args){
    const char * dictpath;
    if (!PyArg_ParseTuple(args, "s",&dictpath)){
        return NULL;
    }
    scws_set_dict(s, dictpath, SCWS_XDICT_TXT);
    return Py_BuildValue("i",1);
}

static PyObject * scws_scws_add_dict(PyObject * self,PyObject * args){
    const char * dictpath;
    if (!PyArg_ParseTuple(args, "s",&dictpath)){
        return NULL;
    }
    scws_add_dict(s, dictpath, SCWS_XDICT_TXT);
    return Py_BuildValue("i",1);
}

static PyObject * scws_scws_set_charset(PyObject * self,PyObject * args){
    const char * charset;

    if (!PyArg_ParseTuple(args, "s",&charset)){
        return NULL;
    }
    scws_set_charset(s, charset);
    return Py_BuildValue("i",1);
}

static PyObject * scws_scws_set_rule(PyObject * self,PyObject * args){
    const char * rule;

    if (!PyArg_ParseTuple(args, "s",&rule)){
        return NULL;
    }
    scws_set_rule(s, rule);
    return Py_BuildValue("i",1);
}

static PyObject * scws_scws_set_ignore(PyObject * self,PyObject * args){
	const int mode;
    if (!PyArg_ParseTuple(args, "i",&mode)){
        return NULL;
    }
    scws_set_ignore(s, mode);
    return Py_BuildValue("i",1);
}

static PyObject * scws_scws_set_multi(PyObject * self,PyObject * args){
	const int mode;
    if (!PyArg_ParseTuple(args, "i",&mode)){
        return NULL;
    }
    scws_set_multi(s, mode);
    return Py_BuildValue("i",1);
}

static PyObject * scws_scws_set_duality(PyObject * self,PyObject * args){
	const int mode;
    if (!PyArg_ParseTuple(args, "i",&mode)){
        return NULL;
    }
    scws_set_ignore(s, mode);
    return Py_BuildValue("i",1);
}


static PyObject * scws_get_res(PyObject * self,PyObject * args){
    const char *text;

    if (!PyArg_ParseTuple(args, "s",&text))
        return NULL;

    scws_res_t res, cur;
    scws_send_text(s, text, strlen(text));
    PyObject * v;
    // int i = 0;
    // int total = 0;
    // long idf;
    // scws_res_t head;
    v = PyList_New(0);
    // double d;
    while ((res = cur = scws_get_result(s)))
    {
        while(cur != NULL){
            PyList_Append(v,Py_BuildValue("(O,O,d)",
                //PyString_FromStringAndSize(text+cur->off,cur->len),
                //PyString_FromString(cur->attr),
				PyUnicode_FromStringAndSize(text+cur->off,cur->len),
				PyUnicode_FromFormat("%s",cur->attr),
                cur->idf));
            cur = cur->next;
        }
    }
    scws_free_result(res);
    return Py_BuildValue("O",v);
}
static PyObject * scws_get_top(PyObject * self,PyObject * args){
    const char *text;

    if (!PyArg_ParseTuple(args, "s",&text))
        return NULL;

    scws_top_t res, cur;
    scws_send_text(s, text, strlen(text));
    PyObject * v;

    v = PyList_New(0);
    // double d;
    res = cur = scws_get_tops(s,10,"@");

    while(cur != NULL){
        PyList_Append(v,Py_BuildValue("(S,d)",
            //PyString_FromStringAndSize(text+cur->off,cur->len),
            //PyString_FromString(cur->attr),
			//PyUnicode_FromStringAndSize(text+cur->off,cur->len),
			PyUnicode_FromFormat("%s",cur->word),
			cur->weight
			)
		);
        cur = cur->next;
    }

    scws_free_tops(res);
    return Py_BuildValue("O",v);
}
static PyObject * scws_scws_free(PyObject * self,PyObject * args){
    scws_free(s);
    return Py_BuildValue("i", 1);
}
static PyMethodDef ScwsMethods[] = {
    {"scws_set_rule",  scws_scws_set_rule, METH_VARARGS, ""},
    {"scws_set_xdb",  scws_set_xdb, METH_VARARGS, ""},
    {"scws_set_txt",  scws_set_txt, METH_VARARGS, ""},
    {"scws_set_charset",  scws_scws_set_charset, METH_VARARGS, ""},
    {"scws_new",  scws_scws_new, METH_VARARGS, ""},
    {"scws_free",  scws_scws_free, METH_VARARGS, ""},
    {"scws_set_ignore", scws_scws_set_ignore, METH_VARARGS, ""},
    {"scws_set_multi", scws_scws_set_multi, METH_VARARGS, ""},
    {"scws_set_duality", scws_scws_set_duality, METH_VARARGS, ""},
    {"scws_add_dict", scws_scws_add_dict, METH_VARARGS, ""},
    {"get_res",  scws_get_res, METH_VARARGS, ""},
    {"get_tops",  scws_get_top, METH_VARARGS, ""},
    {NULL, NULL, 0, NULL}
};
static struct PyModuleDef scws_module = {
	PyModuleDef_HEAD_INIT,
	"scws",        // name of module /
	NULL,                    // module documentation, may be NULL /
	-1,                      // size of per-interpreter state of the module, or -1 if the module keeps state in global variables. /
	ScwsMethods   // A pointer to a table of module-level functions, described by PyMethodDef values. Can be NULL if no functions are present. /
};
PyMODINIT_FUNC PyInit_scws(void)
{
    PyObject * m;
    //m = Py_InitModule("_scws", ScwsMethods);
	m = PyModule_Create(&scws_module);
	if (m == NULL)
		return NULL;
	//printf("init lc_hello_world module\n");
	return m;
}

//gcc scws.c -shared -o scws.so -I/usr/local/Cellar/python3/3.6.4_2/Frameworks/Python.framework/Versions/3.6/include/python3.6m -I/usr/local/scws/include/scws -fPIC -L/usr/local/scws/lib/ -L/usr/local/Cellar/python3/3.6.4_2/Frameworks/Python.framework/Versions/3.6/lib/ -lscws -lpython3.6
