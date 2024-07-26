#include <Python.h>
#include <curl_api.h>

static PyObject* py_login(PyObject* self, PyObject* args)
{
    char* username;
    char* password;
    char* user_agent_designation;
    char* url;
    
    if (!PyArg_ParseTuple(args, "ssss", &username, &password, &user_agent_designation, &url))
    {
        return NULL;
    }

    cookie_t* cookie_jar = login(username, password, user_agent_designation, url);
    if (cookie_jar == NULL)
    {
        Py_RETURN_NONE;
    }

    PyObject* result = Py_BuildValue("{s:s, s:s, s:s, s:s, s:s, s:s, s:s}",
        "domain", cookie_jar->domain,
        "subdomain_bool", cookie_jar->subdomain_bool,
        "path", cookie_jar->path,
        "secure_bool", cookie_jar->secure_bool,
        "date", cookie_jar->date,
        "cookie_name", cookie_jar->cookie_name,
        "cookie_value", cookie_jar->cookie_value);

    return result;
}

static PyObject* py_free_llist(PyObject* self, PyObject* args)
{
    node_t* cookie_jar = NULL;

    if (!PyArg_ParseTuple(args, "(O!)", &PyCapsule_Type, &cookie_jar))
    {
        return NULL;
    }

    free_llist(cookie_jar);

    Py_RETURN_NONE;  
}

static PyMethodDef CurlApiMethods[] = {
    {"login", py_login, METH_VARARGS, "log in to provider"},
    {"free_llist", py_free_llist, METH_VARARGS, "Iterate over linkedList carying cookie data and free the memory."},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef curlapimodule = {
    PyModuleDef_HEAD_INIT,
    "curl_api_module", 
    NULL, 
    -1, 
    CurlApiMethods
};

PyMODINIT_FUNC PyInit_curl_api_module(void)
{
    return PyModule_Create(&curlapimodule);
}