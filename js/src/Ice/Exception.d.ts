// **********************************************************************
//
// Copyright (c) 2003-2018 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

declare module "ice"
{
    namespace Ice
    {
        /**
         * Base class for all Ice exceptions.
         */
        abstract class Exception extends Error
        {
            /**
             * Returns the name of this exception.
             *
             * @return The name of this exception.
             *
             * @deprecated ice_name() is deprecated, use ice_id() instead.
             **/
            ice_name():string;

            /**
             * Returns the type id of this exception.
             *
             * @return The type id of this exception.
             **/
            ice_id():string;

            /**
             * Returns a string representation of this exception.
             *
             * @return A string representation of this exception.
             **/
            toString():string;
        }

        /**
         * Base class for all Ice run-time exceptions.
         */
        abstract class LocalException extends Exception {}

        /**
         * Base class for all Ice user exceptions.
         */
        abstract class UserException extends Exception
        {
            /**
             * Obtains the sliced data associated with this instance.
             * @return The sliced data if the exception has a preserved-slice base class and has been sliced during
             * unmarshaling of the exception, nil otherwise.
             */
            ice_getSlicedData():SlicedData;

            /**
             * Obtains the Slice type ID of this exception.
             * @return The fully-scoped type ID.
             */
            static ice_staticId():string;
        }
    }
}
