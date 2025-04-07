/*
 * Copyright (C) 2021 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package libcore.java.lang.reflect;

import java.lang.reflect.GenericSignatureFormatError;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNull;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.JUnit4;

@RunWith(JUnit4.class)
public class GenericSignatureFormatErrorTest {
    private static final String MESSAGE = "message";

    @Test
    public void constructor() {
        try {
            throw new GenericSignatureFormatError();
        } catch (GenericSignatureFormatError e) {
            assertNull(e.getCause());
            assertNull(e.getMessage());
        }
    }

    @Test
    public void constructorLString() {
        try {
            throw new GenericSignatureFormatError(MESSAGE);
        } catch (GenericSignatureFormatError e) {
            assertNull(e.getCause());
            assertEquals(MESSAGE, e.getMessage());
        }
    }
}
