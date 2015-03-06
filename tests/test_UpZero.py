# * Copyright (C) 2015 Axios, Inc.
# *
# * This program is free software: you can redistribute it and/or modify
# * it under the terms of the GNU General Public License as published by
# * the Free Software Foundation, either version 3 of the License, or
# * (at your option) any later version.
# *
# * This program is distributed in the hope that it will be useful,
# * but WITHOUT ANY WARRANTY; without even the implied warranty of
# * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# * GNU General Public License for more details.
# *
# * You should have received a copy of the GNU General Public License
# * along with this program. If not, see <http://www.gnu.org/licenses/>.
#!/usr/bin/env python
import unittest
import ossie.utils.testing
from ossie.utils import sb
import os
from time import sleep
from omniORB import any

class ResourceTests(ossie.utils.testing.ScaComponentTestCase):
    """Test for all resource implementations in UpZero"""

    def setUp(self):
        #set up 
        ossie.utils.testing.ScaComponentTestCase.setUp(self)
        self.src = sb.DataSource()
        self.sink = sb.DataSink()
        
        #connect 
        self.startComponent()
        self.src.connect(self.comp)
        self.comp.connect(self.sink)
        
        #starts sandbox
        sb.start()

    def tearDown(self):
        #######################################################################
        # Simulate regular resource shutdown
        self.comp.releaseObject()
        
        self.comp.stop()
        sb.reset()
        sb.stop()
        ossie.utils.testing.ScaComponentTestCase.tearDown(self);

    def startComponent(self):
        #######################################################################
        # Launch the resource with the default execparams
        execparams = self.getPropertySet(kinds=("execparam",), modes=("readwrite", "writeonly"), includeNil=False)
        execparams = dict([(x.id, any.from_any(x.value)) for x in execparams])
        self.launch(execparams)

        #######################################################################
        # Verify the basic state of the resource
        self.assertNotEqual(self.comp, None)
        self.assertEqual(self.comp.ref._non_existent(), False)

        self.assertEqual(self.comp.ref._is_a("IDL:CF/Resource:1.0"), True)

        #######################################################################
        # Validate that query returns all expected parameters
        # Query of '[]' should return the following set of properties
        expectedProps = []
        expectedProps.extend(self.getPropertySet(kinds=("configure", "execparam"), modes=("readwrite", "readonly"), includeNil=True))
        expectedProps.extend(self.getPropertySet(kinds=("allocate",), action="external", includeNil=True))
        props = self.comp.query([])
        props = dict((x.id, any.from_any(x.value)) for x in props)
        # Query may return more than expected, but not less
        for expectedProp in expectedProps:
            self.assertEquals(props.has_key(expectedProp.id), True)

        #######################################################################
        # Verify that all expected ports are available
        for port in self.scd.get_componentfeatures().get_ports().get_uses():
            port_obj = self.comp.getPort(str(port.get_usesname()))
            self.assertNotEqual(port_obj, None)
            self.assertEqual(port_obj._non_existent(), False)
            self.assertEqual(port_obj._is_a("IDL:CF/Port:1.0"),  True)

        for port in self.scd.get_componentfeatures().get_ports().get_provides():
            port_obj = self.comp.getPort(str(port.get_providesname()))
            self.assertNotEqual(port_obj, None)
            self.assertEqual(port_obj._non_existent(), False)
            self.assertEqual(port_obj._is_a(port.get_repid()),  True)

        #######################################################################
        # Make sure start and stop can be called without throwing exceptions
        self.comp.start()

    # TODO Add additional tests here
    #
    # See:
    #   ossie.utils.bulkio.bulkio_helpers,
    #   ossie.utils.bluefile.bluefile_helpers
    # for modules that will assist with testing resource with BULKIO ports
    
    
    def testComponantReal(self):
        for z in range(2,15):
            inputData = [float(x) for x in xrange(1000)]
            self.comp.upsample_factor = z
            self.src.push(inputData)
            print "Testing UpZero Real functionality - ", self.comp.upsample_factor
              
            outData = []
            count = 0
            while True:
                outData = self.sink.getData()
                if outData:
                    break
                if count == 100:
                    break;
                sleep(.01)
                count+=1
              
            self.assertEqual(len(inputData)*self.comp.upsample_factor, len(outData))
            for x in xrange(len(inputData)):
                self.assertEqual(inputData[x], outData[x*self.comp.upsample_factor]);
                for i in xrange(self.comp.upsample_factor-1):
                    self.assertEqual(outData[(x*self.comp.upsample_factor)+(i+1)], 0)
                    
    def testComponantComplex(self):
        for z in range(2,15):
            inputData = [complex(float(x+1), -float(x)) for x in xrange(1000)]
            self.comp.upsample_factor = z
            self.src.push(inputData)
            print "Testing UpZero Complex functionality - ", self.comp.upsample_factor
            
            outData = []
            outputData = []
            count = 0
            
            while True:
                outData = self.sink.getData()
                if outData:
                    break
                if count == 100:
                    break;
                sleep(.01)
                count+=1
                
            for i in range(len(outData)/2):
                outputData.append(complex(outData[2*i], outData[2*i+1]))
            
            self.assertEqual(len(inputData)*self.comp.upsample_factor, len(outputData))
            for x in xrange(len(inputData)):
                self.assertEqual(inputData[x], outputData[x*self.comp.upsample_factor]);
                for i in xrange(self.comp.upsample_factor-1):
                    self.assertEqual(outputData[(x*self.comp.upsample_factor)+(i+1)], complex(0,0))

if __name__ == "__main__":
    ossie.utils.testing.main("../UpZero.spd.xml") # By default tests all implementations
