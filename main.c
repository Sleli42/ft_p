/* ==== REQUEST */
#define REQUEST_PUT 	1
#define REQUEST_GET 	2
#define REQUEST_DIR 	3

struct request
{
	int		req;
	int		nbbytes;	/* pour req_put only */
	char	*path;	
};

/* ===== ANSWER */
#define ANSWER_OK		0
#define ANSWER_UNKNOW	1
#define ANSWER_ERROR	2

struct answer
{
	int		ans;
	int		nbbytes;	/* pour get only */
	int		errnum;
};

