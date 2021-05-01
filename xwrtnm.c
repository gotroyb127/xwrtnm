#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

Display *dpy;

int
gettextprop(Window w, Atom atom, char *text, unsigned int size)
{
	char **list = NULL;
	int n;
	XTextProperty name;

	if (!text || size == 0)
		return 0;
	text[0] = '\0';
	if (!XGetTextProperty(dpy, w, &name, atom) || !name.nitems)
		return 0;
	if (name.encoding == XA_STRING)
		strncpy(text, (char *)name.value, size - 1);
	else {
		if (XmbTextPropertyToTextList(dpy, &name, &list, &n) >= Success && n > 0 && *list) {
			strncpy(text, *list, size - 1);
			XFreeStringList(list);
		}
	}
	text[size - 1] = '\0';
	XFree(name.value);
	return 1;
}

int
main(int argc, char *argv[])
{
	int running;
	Window root;
	XEvent ev;
	char str[512];

	dpy = XOpenDisplay(NULL);

	if (!dpy) {
		fprintf(stderr, "%s: cannot open display\n", argv[0]);
		exit(1);
	}

	root = DefaultRootWindow(dpy);
	XSelectInput(dpy, root, PropertyChangeMask);

	for (running = 1; running;) {
		XNextEvent(dpy, &ev);
		if (ev.xproperty.atom != XA_WM_NAME)
			continue;

		gettextprop(root, XA_WM_NAME, str, sizeof str);
		puts(str);
		fflush(stdout);
	}

	XCloseDisplay(dpy);

	return 0;
}
