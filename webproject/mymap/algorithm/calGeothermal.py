#!/usr/bin/env python
# coding: utf-8

# In[1]:


import pandas as pd


# In[12]:

class Geothermal:
	# global self.data1,self.data2,self.grdHt,self.grdPos,self.grdTmprt

	def __init__(self, dtdir):
		self.data1 = pd.read_excel(dtdir+'data.xlsx').values
		self.data2 = pd.read_excel(dtdir+'latlog.xlsx').values


		self.grdHt = [self.data2[0,3] ]
		for i in range(6):
		    self.grdHt.append( self.grdHt[-1]- self.data1[i,2]*self.data1[i,3] )


		# In[52]:


		self.grdTmprt = [self.data2[0,4]]
		for i in range(6):
		    self.grdTmprt.append( self.grdTmprt[-1] +  self.grdHt[i]*self.data1[i,2]/self.data1[i,4] - self.data1[i,3]*self.data1[i,2]*self.data1[i,2]/(2*self.data1[i,4]))


		# In[54]:


		self.grdPos = [0]
		for i in range(6):
		    self.grdPos.append( self.grdPos[-1] + self.data1[i,2])


	def caldepPos(self, dep ):
	    idx = -1
	    if dep>=self.grdPos[-1]:
	        idx = len( self.grdPos )-1
	    else:
	        for i in range( len(self.grdPos )-1):
	            if dep>=self.grdPos[i] and dep<self.grdPos[i+1]:
	                idx = i 
	                break
	    return idx


	# In[69]:


	def caltmprt(self, dep ):
	    pos = self.caldepPos( dep )
	    thck = dep - self.grdPos[pos]
	    # print(self.grdTmprt[pos],self.grdHt[pos],thck,self.data1[pos,4],self.data1[pos,3])
	    return self.grdTmprt[pos] + self.grdHt[pos]*thck/self.data1[pos,4] - self.data1[pos,3]*thck*thck/(2*self.data1[pos,4])

# %%
