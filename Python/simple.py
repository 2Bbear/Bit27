#-*- coding: utf-8 -*-

def HelloWorld():
    data = 'Hello World C#'
    return data

def HelloWorldKorean():
    data='안녕하세요'
    return data

def HelloWorld2( data ):
    return data
 
def ListTest():
    
    data = []
    data.append('Hello')
    data.append('World')
    data.append('black falcon')
    data.append("블랙팔콘")
    return data
 
class MyClass(object):
    def __init__(self, value):
        self.value = value
#한글

