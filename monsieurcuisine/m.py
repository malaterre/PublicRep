import smtplib
# email options
SERVER = "smtp.free.fr"
FROM = "malat@free.fr"
TO = ["malat@debian.org"]
SUBJECT = "Alert!"
TEXT = "This message was sent with Python's smtplib."


message = """\
From: %s
To: %s
Subject: %s

%s
""" % (FROM, ", ".join(TO), SUBJECT, TEXT)

server = smtplib.SMTP(SERVER)
#server.set_debuglevel(3)
server.sendmail(FROM, TO, message)
server.quit()
