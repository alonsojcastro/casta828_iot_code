#!/usr/bin/env python

############## summary of mail ##############

import subprocess
import smtplib
import socket
import time from email.mime.text 
import MIMEText
import datetime
import urllib2

import feedparser	
import time	

to = 'casta828@newschool.edu'
gmail_user = 'casta828@newschool.edu'
gmail_password = '****'
smtpserver = smtplib.SMTP('smtp.gmail.com', 587)
smtpserver.ehlo()
smtpserver.starttls()
smtpserver.ehlo
smtpserver.login(gmail_user, gmail_password)
today = datetime.date.today()

# Very Linux Specific
arg='ip route list'
p=subprocess.Popen(arg,shell=True,stdout=subprocess.PIPE)
data = p.communicate()
split_data = data[0].split()
ipaddr = split_data[split_data.index('src')+1]
extipaddr = urllib2.urlopen("http://icanhazip.com").read()
my_ip = 'Local address: %s\nExternal address: %s' %  (ipaddr, extipaddr)
msg = MIMEText(my_ip)
msg['Subject'] = 'IP For RaspberryPi on %s' % today.strftime('%b %d %Y')
msg['From'] = gmail_user
msg['To'] = to
time.sleep(5)
smtpserver.sendmail(gmail_user, [to], msg.as_string())
smtpserver.quit()

user='casta828@newschool.edu'		
passwd='Quienmassoyyo?'	

while True: 
newmails = feedparser.parse("https://" + user + ":" + passwd + "@mail.google.com/gmail/feed/atom").entries
for i in newmails:		
    print str(i.summary)		
    if str(i.summary)=="us@mfadt.parsons.edu":	
        print i.summary
     
     def emailcount(n):
    	if n > 1: 
            print "you have "+str(n)+" new email(s)"
        else: 
            print "you have no new email"

    emailcount(newmails)
    time.sleep(10)	








