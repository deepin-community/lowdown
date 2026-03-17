#include <err.h>
#include <stdio.h>
#include <string.h>
#include <sys/queue.h>
#include <lowdown.h>

int main(int argc, char *argv[])
{
    const char *text = "# This is a header";

    struct lowdown_doc *doc = lowdown_doc_new(NULL);
    if (!doc)
        err(2, "Cannot allocate document");

    size_t maxn = 0;
    struct lowdown_node *node = lowdown_doc_parse(doc, &maxn, text, strlen(text), NULL);
    if (!node)
        err(3, "Cannot parse document");

    void *renderer = lowdown_html_new(NULL);
    if (!renderer)
        err(4, "Cannot allocate renderer");

    struct lowdown_buf *buf = lowdown_buf_new(16384);
    if (!buf)
        err(5, "Cannot allocate output buffer");

    int rndr_res = lowdown_html_rndr(buf, renderer, node);
    if (!rndr_res)
        err(6, "Allocation error while rendering Markdown");

    fwrite(buf->data, 1, buf->size, stdout);

    lowdown_html_free(renderer);
    lowdown_buf_free(buf);
    lowdown_node_free(node);
    lowdown_doc_free(doc);

    return 0;
}
