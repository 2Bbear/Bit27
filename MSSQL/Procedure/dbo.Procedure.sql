
CREATE PROCEDURE [dbo].[AddProduct2]
	@PNAME varchar(50),
	@Balance int,
	@Description varchar(MAX)
AS
	insert into jjhAccount(NAME, Balance, Description)
	values (@PNAME, @Balance, @Description)
RETURN 0
